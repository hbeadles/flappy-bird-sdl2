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
    background = loadTexture(game->app, "gfx/background-v2.png");
    base = loadTexture(game->app, "gfx/base_brown.png");
    gameOverTexture = loadTextTexture(game->app, "Game Over", {255, 191, 0}, game->textWriter.getFont());
    restartText = loadTextTexture(game->app, "Restart?", {0xff, 255, 0xff}, game->textWriter.getFont());
    hitEnter = loadTextTexture(game->app, "Hit Enter", {205, 127, 50}, game->textWriter.getFont());
    SDL_QueryTexture(gameOverTexture, nullptr, nullptr, &gameOverTextureWidth, &gameOverTextureHeight);
    SDL_QueryTexture(restartText, nullptr, nullptr, &restartTextWidth, &restartTextHeight);
    SDL_QueryTexture(hitEnter, nullptr, nullptr, &hitEnterWidth, &hitEnterHeight);
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
    bool spacePressed = state[SDL_SCANCODE_SPACE] && !game->spaceWasPressed;
    bool returnPressed = state[SDL_SCANCODE_RETURN] && !game->returnWasPressed;
    if (spacePressed || returnPressed) {
        printf("Restarting game...\n");
        restart = true;
    }
}

StageType GameOverStage::update(float deltaTime) {
    backgroundY += deltaTime * 50;
    if (backgroundY >= (SCREEN_HEIGHT / 2 - gameOverTextureHeight * 3)) {
        backgroundY = (SCREEN_HEIGHT / 2 - gameOverTextureHeight * 3);
    }
    if (restart) {
        return StageType::GAME_INTRO;
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
    blit(game->app, restartText,
    SCREEN_WIDTH / 2 - (restartTextWidth / 2),  backgroundY + gameOverTextureHeight + 20, 0, SDL_FLIP_NONE);
    blit(game->app, hitEnter,
        SCREEN_WIDTH / 2 - (hitEnterWidth / 2),  backgroundY + gameOverTextureHeight + restartTextHeight + 40, 0, SDL_FLIP_NONE);
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
