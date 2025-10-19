//
// Created by Hayden Beadles on 10/8/25.
//
#include <game/gameover.h>
#include <game/game.h>
#include <draw/textures.h>
#include <draw/draw.h>

/**
 * @name GameOverStage
 * @brief Constructor for GameOverStage class. Setup initial values
 * @param game Game object, dependency injection
 * @memberof GameOverStage
 */
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

/**
 * @name init
 * @brief Initializes the Game Over stage, loading textures and setting initial positions
 * @memberof GameOverStage
 */
void GameOverStage::init() {
    background = loadTexture(game->app, "gfx/background-2.png");
    colorModulate(background, 200, 200, 200);
    base = loadTexture(game->app, "gfx/base_dark_large.png");
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

/**
 * @name reset
 * @brief Resets the Game Over stage to its initial state
 * @memberof GameOverStage
 */
void GameOverStage::reset() {
    backgroundY = 0;
    backgroundX = 0;
    baseX = 0;
    game->score = 0;
    restart = false;
}

/**
 * @name handleInput
 * @brief Handles user input for the Game Over stage
 * @param state Current keyboard state
 * @memberof GameOverStage
 */
void GameOverStage::handleInput(const Uint8* state) {
    bool spacePressed = state[SDL_SCANCODE_SPACE] && !game->spaceWasPressed;
    bool returnPressed = state[SDL_SCANCODE_RETURN] && !game->returnWasPressed;
    if (spacePressed || returnPressed) {
        printf("Restarting game...\n");
        restart = true;
    }
}

/**
 * @name update
 * @brief Updates the Game Over stage, animating the background and transitioning to intro on restart
 * @param deltaTime Time elapsed since last frame
 * @return StageType - Next stage to transition to, or NONE if no transition
 * @memberof GameOverStage
 */
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

/**
 * @name draw
 * @brief Draws the Game Over stage, including background, base, and game over text
 * @memberof GameOverStage
 */
void GameOverStage::draw() {
    drawBackground();
    if (hasPipeManager()) {
        game->pipe_manager->drawPipes();
    }
    drawBase();
    drawGameOver();
}

/**
 * @name drawGameOver
 * @brief Draws the Game Over text and restart prompt on the screen
 * @memberof GameOverStage
 */
void GameOverStage::drawGameOver() {
    blit(game->app, gameOverTexture,
        SCREEN_WIDTH / 2 - (gameOverTextureWidth / 2),  backgroundY, 0, SDL_FLIP_NONE);
    blit(game->app, restartText,
    SCREEN_WIDTH / 2 - (restartTextWidth / 2),  backgroundY + gameOverTextureHeight + 20, 0, SDL_FLIP_NONE);
    blit(game->app, hitEnter,
        SCREEN_WIDTH / 2 - (hitEnterWidth / 2),  backgroundY + gameOverTextureHeight + restartTextHeight + 40, 0, SDL_FLIP_NONE);
}

/**
 * @name drawBackground
 * @brief Draws the scrolling background texture
 * @memberof GameOverStage
 */
void GameOverStage::drawBackground() {
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
    }
}

/**
 * @name drawBase
 * @brief Draws the scrolling base texture at the bottom of the screen
 * @memberof GameOverStage
 */
void GameOverStage::drawBase() {
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
