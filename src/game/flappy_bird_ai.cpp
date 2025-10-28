//
// Created by Hayden Beadles on 10/24/25.
//

#include <game/flappy_bird_ai.h>
#include <game/game.h>
#include <utils/utils.h>

FlappyAI::FlappyAI(Game* game) : game(game), mState(IDLE) {
}


void FlappyAI::update(Flappy* flappy, PipeManager* pipeManager, float deltaTime) {
    reset();
    flappy->y += flappy->dy * deltaTime;
    flappy->x += flappy->dx * deltaTime;
    flappy->dy += GRAVITY * 60.0f;

    float targetRotation = flappy->dy * FLAPPY_ROTATION_SPEED * deltaTime;
    targetRotation = std::clamp(targetRotation, -35.0f, FLAPPY_MAX_ROTATION);
    flappy->jumpAngle = targetRotation;

    pipeMidPoints = calculateMidPoints(flappy, pipeManager);
    // Get the closest pipe midPoint to our FlappyBird
    double minDistance = 1000.0f;
    SDL_Point chosenPoint = {};
    SDL_Point flappyCoords = {(int)flappy->x, (int)flappy->y};
    for (auto& point: pipeMidPoints) {
        // Give me the point closest to my flappy bird
        if (point.x > flappyCoords.x) {
            double d = distance(point, flappyCoords);
            if (d < minDistance) {
                minDistance = d;
                chosenPoint = point;
            }
        }
    }
    if (game->debug) {
        std::sort(pipeMidPoints.begin(), pipeMidPoints.end(),
              [&](const SDL_Point& a, const SDL_Point& b) {
                  return distance(a, flappyCoords) < distance(b, flappyCoords);
              });
    }
    if (minDistance < 1000.0f) {
        // Check the angle
        double angle = angleBetweenPoints(chosenPoint, flappyCoords);
        double angleDegrees = angle * 180.0 / M_PI;
        if (angleDegrees <= 5) {
            // do nothing
        }else {
            if (flappy->active) {
                flappy->dy = -125.0f;
                flappy->jumpAngle = -35.0f;
                if (!flappy->isJumping) {
                    flappy->isJumping = true;
                    flappy->animTimer = 0.0f;
                    flappy->currentFrame = 0;
                }
            }
        }

    }
    if (flappy->active) {
        for (Pipe& pipe : pipeManager->pipePool){
            if (pipe.active && collision(flappy, &pipe)){
                CollisionSide side = getCollisionSide(flappy, &pipe);
                if (flappy->active) {
                    //playSound("hit");
                }
                switch(side) {
                    case SIDE_TOP:
                        // Bird hit top of pipe - bounce up
                        flappy->dy = -abs(flappy->dy);
                        flappy->y = pipe.y - flappy->idleTexture->rect.h - 1;

                        break;
                    case SIDE_BOTTOM:
                        // Bird hit bottom of pipe - bounce down
                        flappy->dy = abs(flappy->dy);
                        flappy->y = pipe.y + pipe.texture->rect.h + 1;
                        break;
                    case SIDE_LEFT:
                        // Bird hit left side of pipe - bounce left
                        flappy->dx = -abs(flappy->dx);
                        flappy->x = pipe.x - flappy->idleTexture->rect.w - 1;
                        break;
                    case SIDE_RIGHT:
                        // Bird hit right side of pipe - bounce right
                        flappy->dx = abs(flappy->dx);
                        flappy->x = pipe.x + pipe.texture->rect.w + 1;
                        break;
                    default:
                        break;
                }
            }
        }
    }
    if (flappy->y < 0.0f) {
        flappy->health--;
    }
    if (flappy->y > (SCREEN_HEIGHT - BASE_HEIGHT - flappy->idleTexture->rect.h)) {
        flappy->health--;
        flappy->y = SCREEN_HEIGHT - BASE_HEIGHT - flappy->idleTexture->rect.h;
    }
    int offsetX = (SCREEN_WIDTH - BACKGROUND_WIDTH) / 2;

    if (flappy->x < -offsetX) {
        flappy->health--;
        flappy->x = -offsetX;
    }
    if (flappy->x > SCREEN_WIDTH) {
        flappy->health--;
        flappy->x = SCREEN_WIDTH;
    }

    if (flappy->health <= 0){
        flappy->active = false;
    }

    if (flappy->isJumping) {
        flappy->animTimer += deltaTime;
        if (flappy->animTimer >= flappy->frameTime) {
            flappy->animTimer = 0.0f;
            flappy->currentFrame++;
            if (flappy->currentFrame >= flappy->jumpTextures.size()) {
                flappy->currentFrame = 0;
                flappy->isJumping = false;
            }
        }
    }

}


std::vector<SDL_Point> FlappyAI::calculateMidPoints(Flappy* flappy, PipeManager *pipeManager) {
    std::vector<SDL_Point> result;
    // SDL_Point startingPoint = {(int)flappy->x + (flappy->idleTexture->rect.w / 2),
        // (int)flappy->y + (flappy->idleTexture->rect.h / 2)};
    // result.insert( result.begin(), startingPoint);
    for (auto& pipe: pipeManager->pipePool) {
        if (!pipe.passed) {
            if (!pipe.isTop && pipe.active && flappy->active) {
                result.push_back({(int)pipe.midX, (int)pipe.midY});
            }

        }
    }
    int offsetX = (SCREEN_WIDTH - BACKGROUND_WIDTH) / 2;
    SDL_Point endPoint = {-offsetX + SCREEN_WIDTH, (int)flappy->y};
    result.push_back(endPoint);
    return result;
}

void FlappyAI::draw(Flappy * flappy) {
    if (game->debug) {
        Vec2 startPos = {(float)flappy->x + (flappy->idleTexture->rect.w / 2),
                         (float)flappy->y + (flappy->idleTexture->rect.h / 2)};
        Vec2 endPos = {startPos.x + 35, startPos.y};
        Vec2 endRotatePos = {startPos.x, startPos.y + 35};
        bezierRGBASDL(game->app.renderer, pipeMidPoints, 15, 255, 128, 0, 255);
        drawArrow(game->app, startPos.x, startPos.y,
            endPos.x, endPos.y, {0, 255, 0, 255});
        drawArrow(game->app, startPos.x, startPos.y,
            endRotatePos.x, endRotatePos.y, {255, 0, 0, 255});
    }
    if (flappy->isJumping) {
        blitAtlasImage(game->app,
            flappy->jumpTextures[flappy->currentFrame],
            flappy->x,
            flappy->y,
            0,
            flappy->jumpAngle,
            SDL_FLIP_NONE);
    }else {
        blitAtlasImage(game->app,
            flappy->idleTexture,
            flappy->x,
            flappy->y,
            0,
            flappy->jumpAngle,
            SDL_FLIP_NONE);
    }
}



void FlappyAI::reset() {
    pipeMidPoints.clear();
}
