//
// Created by Hayden Beadles on 10/9/25.
//
#include <game/gameintro.h>
#include <game/game.h>
#include <draw/textures.h>
#include <draw/draw.h>

GameIntroStage::GameIntroStage(Game *game) : Stage(game, StageType::GAME_INTRO),
                                           background(nullptr),
                                           base(nullptr),
                                           gameIntroTexture(nullptr),
                                           backgroundX(0),
                                           backgroundY(0),
                                           baseX(0),
                                           gameIntroTextureWidth(0),
                                           gameIntroTextureHeight(0)
{
}

void GameIntroStage::init() {
    background = loadTexture(game->app, "gfx/background-day.png");
    base = loadTexture(game->app, "gfx/base.png");
    gameIntroTexture = loadTexture(game->app, "gfx/message.png");
    int w, h;
    SDL_QueryTexture(gameIntroTexture, NULL, NULL, &w, &h);
    gameIntroTextureWidth = w;
    gameIntroTextureHeight = h;
    backgroundY = 0;
    backgroundX = 0;
    baseX = 0;
}

void GameIntroStage::reset() {
    backgroundY = 0;
    backgroundX = 0;
    baseX = 0;
    game->score = 0;
    start = false;
}

void GameIntroStage::handleInput(const Uint8* state) {
    bool spacePressed = state[SDL_SCANCODE_SPACE] && !game->spaceWasPressed;
    bool returnPressed = state[SDL_SCANCODE_RETURN] && !game->returnWasPressed;

    if (spacePressed || returnPressed) {
        printf("Starting game...\n");
        start = true;
    }
}

StageType GameIntroStage::update(float deltaTime) {
    backgroundY += deltaTime * 50;
    if (backgroundY >= (SCREEN_HEIGHT / 2 - gameIntroTextureHeight / 2)) {
        backgroundY = (SCREEN_HEIGHT / 2 - gameIntroTextureHeight / 2);
    }
    if (start) {
        return StageType::GAMEPLAY;
    }

    return StageType::NONE;
}

void GameIntroStage::draw() {
    drawBackground();
    drawBase();
    drawIntro();
}

void GameIntroStage::drawIntro() {
    blit(game->app, gameIntroTexture,
        SCREEN_WIDTH / 2 - (gameIntroTextureWidth / 2),  backgroundY, 0, SDL_FLIP_NONE);
}


void GameIntroStage::drawBackground() {
    for (double x = backgroundX; x < SCREEN_WIDTH; x += SCREEN_WIDTH) {
        blit(game->app, background, x, 0);
    }
}

void GameIntroStage::drawBase() {
    for (double x = baseX; x < SCREEN_WIDTH; x += SCREEN_WIDTH) {
        blit(game->app, base, x, SCREEN_HEIGHT - BASE_HEIGHT);
    }
}

