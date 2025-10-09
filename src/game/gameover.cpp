//
// Created by Hayden Beadles on 10/8/25.
//
#include <game/gameover.h>
#include <game/game.h>
#include <draw/textures.h>
#include <draw/draw.h>

GameOverStage::GameOverStage(Game *game) : Stage(game, StageType::GAME_OVER),
                                           background(nullptr),
                                           base(nullptr),
                                           gameOverTexture(nullptr),
                                           backgroundX(0),
                                           backgroundY(0),
                                           baseX(0),
                                           gameOverTextureWidth(0),
                                           gameOverTextureHeight(0)
{
}

void GameOverStage::init() {
    background = loadTexture(game->app, "gfx/background-day.png");
    base = loadTexture(game->app, "gfx/base.png");
    gameOverTexture = loadTexture(game->app, "gfx/gameover.png");
    int w, h;
    SDL_QueryTexture(gameOverTexture, NULL, NULL, &w, &h);
    gameOverTextureWidth = w;
    gameOverTextureHeight = h;
    backgroundY = 0;
    backgroundX = 0;
    baseX = 0;
}

void GameOverStage::reset() {
    backgroundY = 0;
    backgroundX = 0;
    baseX = 0;
    game->score = 0;
    restart = false;
}
void GameOverStage::handleInput(const Uint8* state) {
    if (state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_RETURN]) {
        printf("Restarting game...\n");
        restart = true;
    }
}

StageType GameOverStage::update(float deltaTime) {
    backgroundY += deltaTime * 50;
    if (backgroundY >= (SCREEN_HEIGHT / 2 - gameOverTextureHeight)) {
        backgroundY = (SCREEN_HEIGHT / 2 - gameOverTextureHeight);
    }
    if (restart) {
        return StageType::GAMEPLAY;
    }

    return StageType::NONE;
}

void GameOverStage::draw() {
    drawBackground();
    if (hasPipeManager()) {
        game->pipe_manager->drawPipes();
    }
    drawBase();
    drawGameOver();
}


void GameOverStage::drawGameOver() {
    blit(game->app, gameOverTexture,
        SCREEN_WIDTH / 2 - (gameOverTextureWidth / 2),  backgroundY, 0, SDL_FLIP_NONE);
}


void GameOverStage::drawBackground() {
    for (double x = backgroundX; x < SCREEN_WIDTH; x += SCREEN_WIDTH) {
        blit(game->app, background, x, 0);
    }
}

void GameOverStage::drawBase() {
    for (double x = baseX; x < SCREEN_WIDTH; x += SCREEN_WIDTH) {
        blit(game->app, base, x, SCREEN_HEIGHT - BASE_HEIGHT);
    }
}
