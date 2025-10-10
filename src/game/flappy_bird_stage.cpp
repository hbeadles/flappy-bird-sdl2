//
// Created by Hayden Beadles on 10/5/25.
//
#include <game/flappy_bird_stage.h>
#include <game/game.h>
#include <draw/textures.h>
#include <draw/draw.h>


FlappyBirdStage::FlappyBirdStage(Game *game)
    : Stage(game, StageType::GAMEPLAY),
      textWriter(game),
      background(nullptr),
      base(nullptr),
      backgroundX(0),
      baseX(0) {
};


void FlappyBirdStage::init() {
    background = loadTexture(game->app, "gfx/background-day.png");
    base = loadTexture(game->app, "gfx/base.png");
    if (hasPipeManager()) {
        game->pipe_manager->initPipes();
    }
    textWriter.initText();
};

void FlappyBirdStage::reset() {
    backgroundX = 0;
    baseX = 0;
    game->score = 0;
    if (hasPipeManager()){
        game->pipe_manager->clearPipes();
    }
};

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

void FlappyBirdStage::draw() {

    drawBackground();
    if (hasPipeManager()) {
        game->pipe_manager->drawPipes();
    }
    drawBase();
    textWriter.drawScore(game->score, (SCREEN_WIDTH / 2) - 24, 50);

}

void FlappyBirdStage::drawBackground() {
    for (double x = backgroundX; x < SCREEN_WIDTH; x += SCREEN_WIDTH) {
        blit(game->app, background, x, 0);
    }
}

void FlappyBirdStage::drawBase() {
    for (double x = baseX; x < SCREEN_WIDTH; x += SCREEN_WIDTH) {
        blit(game->app, base, x, SCREEN_HEIGHT - BASE_HEIGHT);
    }
}

void FlappyBirdStage::handleInput(const Uint8* state) {

}