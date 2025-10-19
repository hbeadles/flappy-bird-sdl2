//
// Created by Hayden Beadles on 10/5/25.
//
#include <game/flappy_bird_stage.h>
#include <game/game.h>
#include <draw/textures.h>
#include <draw/draw.h>

/**
 * @name FlappyBirdStage
 * @brief Constructor for FlappyBirdStage class
 * @memberof FlappyBirdStage
 * @param game
 */
FlappyBirdStage::FlappyBirdStage(Game *game)
    : Stage(game, StageType::GAMEPLAY),
      background(nullptr),
      base(nullptr),
      backgroundX(0),
      baseX(0) {
};

/**
 * @name init
 * @brief Sets up Flappy Bird main game textures. Sets up pipe manager
 * @memberof FlappyBirdStage
 */
void FlappyBirdStage::init() {
    background = loadTexture(game->app, "gfx/background-2.png");
    colorModulate(background, 200, 200, 200);
    base = loadTexture(game->app, "gfx/base_dark_large.png");
    if (hasPipeManager()) {
        game->pipe_manager->initPipes();
    }
};

/**
 * @name reset
 * @brief Resets the Flappy Bird stage to initial state
 * @memberof FlappyBirdStage
 */
void FlappyBirdStage::reset() {
    backgroundX = 0;
    baseX = 0;
    game->score = 0;
    if (hasPipeManager()){
        game->pipe_manager->clearPipes();
    }
};

/**
 * @name update
 * @brief Updates the Flappy Bird stage each frame
 * @memberof FlappyBirdStage
 * @param deltaTime
 * @return StageType - Are we transitioning? Return the stage if so, else None
 */
StageType FlappyBirdStage::update(float deltaTime) {
    backgroundX -= deltaTime * 50;

    if (backgroundX <= -SCREEN_WIDTH) {
        backgroundX = 0;
    }
    baseX -= (deltaTime * 100);
    if (baseX <= -SCREEN_WIDTH) {
        baseX = 0;
    }

    if (hasPipeManager()) {
        game->pipe_manager->updatePipes(game->flappy.get(), deltaTime);
    }
    if (game->flappy && game->flappy->active == false) {
        gameOverTimer--;
        if (gameOverTimer <= 0) {
            printf("Game over. Restarting...\n");
            gameOverTimer = FPS * 3;
            return StageType::GAME_OVER;
        }
    }

    return StageType::NONE;
}

/**
 * @name draw
 * @brief Draws the Flappy Bird stage each frame
 * @memberof FlappyBirdStage
 */
void FlappyBirdStage::draw() {

    drawBackground();
    if (hasPipeManager()) {
        game->pipe_manager->drawPipes();
    }
    drawBase();
    game->textWriter.drawScore(game->score, (SCREEN_WIDTH / 2) - 24, 50);

}

/**
 * @name drawBackground
 * @brief Draws the scrolling background
 * @memberof FlappyBirdStage
 */
void FlappyBirdStage::drawBackground() {
    SDL_Point center = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    int w, h;
    SDL_QueryTexture(background, nullptr, nullptr, &w, &h);

    for (double x = backgroundX; x < SCREEN_WIDTH; x += SCREEN_WIDTH) {
        SDL_Rect srcRect ={
            0,
            0,
            w,h
        };
        SDL_Rect dstRect = {
            (int)x, 0, SCREEN_WIDTH, SCREEN_HEIGHT
        };
        blitEx(game->app, background, &srcRect, &dstRect, 0.0, &center, SDL_FLIP_NONE);
        //blit(game->app, background, x, 0, 45.0);
    }
}

/**
 * @name drawBase
 * @brief Draws the scrolling base
 * @memberof FlappyBirdStage
 */
void FlappyBirdStage::drawBase() {
    SDL_Point center = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    int w, h;
    SDL_QueryTexture(base, nullptr, nullptr, &w, &h);
    for (double x = baseX; x < SCREEN_WIDTH; x += SCREEN_WIDTH) {
        SDL_Rect srcRect ={
            0,
            0,
            w,h
        };
        SDL_Rect dstRect = {
            (int) x, SCREEN_HEIGHT - BASE_HEIGHT, w, h
        };
        blitEx(game->app, base, &srcRect, &dstRect, 0.0, &center, SDL_FLIP_NONE);
    }
}

void FlappyBirdStage::handleInput(const Uint8* state) {

}