//
// Created by Hayden Beadles on 10/8/25.
//
#include <game/pipemanager.h>
#include <system/atlas.h>
#include <game/game.h>
#include <draw/draw.h>

/**
 * @brief Constructor for PipeManager class
 * @param game Game object, dependency injection
 * @memberof PipeManager
 */
PipeManager::PipeManager(Game* game): game(game) {

}

/**
 * @name initPipes
 * @brief Initializes the pipe pool with inactive pipes and loads the pipe texture.
 * Called in the constructor.
 * @memberof PipeManager
 */
void PipeManager::initPipes() {
    if (pipeTexture == nullptr) {
        pipeTexture = getAtlasImage(game->app, "gfx/pipe-green.png");
    }
    for (int i = 0; i < TOTAL_PIPES; i++) {
        Pipe pipe;
        pipe.isTop = (i%2 == 0);
        pipe.x = 0.0f;
        pipe.y = 0.0f;
        pipe.texture = pipeTexture;
        pipe.active = false;
        pipePool.push_back(pipe);
    }
    spawnTimer = 0.0f;
}

/**
 * @name randomFloat
 * @brief Generates a random float between min and max
 * @param min Minimum float value
 * @param max Maximum float value
 * @return Random float between min and max
 * @memberof PipeManager
 */
float PipeManager::randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / RAND_MAX * (max - min);
}

/**
 * @name containsInactivePipe
 * @brief Checks if there is an inactive pipe in the pool
 * @param isTop Boolean indicating if checking for top or bottom pipe
 * @return True if there is an inactive pipe, false otherwise
 * @memberof PipeManager
 */
bool PipeManager::containsInactivePipe(bool isTop) {
    for (auto& pipe: pipePool) {
        if (!pipe.active && pipe.isTop == isTop) {
            return true;
        }
    }
    return false;
}

/**
 * @name generatePipePair
 * @brief Generates a pair of pipes (top and bottom) with a gap between them. This is the
 * main function that creates the pipe positions.
 * @param topY Reference to float to store top pipe Y position
 * @param bottomY Reference to float to store bottom pipe Y position
 * @param gap Reference to float to store gap height
 * @param gapMin Minimum gap height
 * @param gapMax Maximum gap height
 * @param gapFraction Fraction (0.0 to 1.0) to interpolate between min and max gap height
 * @memberof PipeManager
 */
void PipeManager::generatePipePair(float &topY, float &bottomY, float &gap,
    float gapMin, float gapMax, float gapFraction) {

    gapFraction = std::clamp(gapFraction, 0.0f, 1.0f);
    float gapHeight = gapMin + (gapMax - gapMin) * gapFraction;

    float maxGapY = (SCREEN_HEIGHT - BASE_HEIGHT) - gapHeight - (PIPE_HEIGHT) + 50;
    // so top pipe doesn't fully go offscreen (optional)
    float minGapY = PIPE_HEIGHT - BASE_HEIGHT;
    float gapY = randomFloat(minGapY, maxGapY);
    topY = gapY - PIPE_HEIGHT;
    bottomY = gapY + gapHeight;
    gap = gapHeight;
}


/**
 * @name updatePipes
 * @brief Updates the position of active pipes, spawns new pipes at intervals, and checks for scoring.
 * @param flappy Pointer to Flappy object for collision and scoring
 * @param deltaTime Time elapsed since last frame
 * @memberof PipeManager
 */
void PipeManager::updatePipes(Flappy* flappy, float deltaTime) {
    spawnTimer -= (deltaTime * 60);
    if (spawnTimer <= 0.0f) {
        spawnTimer = PIPE_SPAWN_INTERVAL;
        // Check if bottom and top pipe are available in pool
        if (containsInactivePipe(false) && containsInactivePipe(true)){
            auto bottomPipe = std::find_if(pipePool.begin(), pipePool.end(), [](const Pipe& pipe){
                return !pipe.active && !pipe.isTop;
            });
            auto topPipe = std::find_if(pipePool.begin(), pipePool.end(), [](const Pipe& pipe){
                return !pipe.active && pipe.isTop;
            });
            float topY, bottomY, gap;
            generatePipePair(topY, bottomY, gap, G_MIN, 100, .5f);
            bottomPipe->active = true;
            bottomPipe->x = SCREEN_WIDTH;
            bottomPipe->y = bottomY;
            bottomPipe->passed = false;  // Reset passed flag
            topPipe->active = true;
            topPipe->x = SCREEN_WIDTH;
            topPipe->y = topY;
            topPipe->passed = false;  // Reset passed flag
        }
    }
    for (auto& pipe: pipePool){
        if (pipe.active){
            if (!pipe.isTop && !pipe.passed && flappy->active){
                if (flappy->x > pipe.x + pipeTexture->rect.w){
                    pipe.passed = true;
                    game->score++;
                }
            }
            pipe.x -= (PIPE_SCROLL_SPEED * deltaTime * 60);
            if (pipe.x + pipeTexture->rect.w < 0){
                pipe.active = false;
                // Note: Don't reset passed flag here, let it reset on spawn
            }
        }
    }

}

/**
 * @name drawPipes
 * @brief Draws all active pipes on the screen
 * @memberof PipeManager
 */
void PipeManager::drawPipes() {
    for (auto& pipe: pipePool) {
        if (pipe.active) {
            blitAtlasImage(game->app, pipeTexture, pipe.x, pipe.y, 0, 0, pipe.isTop ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
        }
    }
}

/**
 * @name clearPipes
 * @brief Clears all pipes from the pool
 * @memberof PipeManager
 */
void PipeManager::clearPipes() {
    pipePool.clear();
}
