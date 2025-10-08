//
// Created by Hayden Beadles on 10/5/25.
//
#include <flappy_bird_stage.h>
#include <game.h>
#include <textures.h>
#include <draw.h>

FlappyBirdStage::FlappyBirdStage(Game *game)
    : Stage(game, StageType::GAMEPLAY), background(nullptr), base(nullptr), backgroundX(0), baseX(0) {
};


void FlappyBirdStage::init() {
    background = loadTexture(game->app, "gfx/background-day.png");
    base = loadTexture(game->app, "gfx/base.png");
    reset();
};

void FlappyBirdStage::reset() {
    backgroundX = 0;
    baseX = 0;
    game->score = 0;

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

    return StageType::NONE;
}

void FlappyBirdStage::draw() {
    drawBackground();
    drawBase();
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