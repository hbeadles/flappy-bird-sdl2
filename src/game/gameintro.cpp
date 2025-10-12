//
// Created by Hayden Beadles on 10/9/25.
//
#include <game/gameintro.h>
#include <game/game.h>
#include <draw/textures.h>
#include <draw/draw.h>

/**
 * @name GameIntroStage
 * @brief Constructor for GameIntroStage class. Setup initial values
 * @param game Game object, dependency injection
 * @memberof GameIntroStage
 */
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

/**
 * @name init
 * @brief Initializes the Game Intro stage, loading textures and setting initial positions
 * @memberof GameIntroStage
 */
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

/**
 * @name reset
 * @brief Resets the Game Intro stage to its initial state
 * @memberof GameIntroStage
 */
void GameIntroStage::reset() {
    backgroundY = 0;
    backgroundX = 0;
    baseX = 0;
    game->score = 0;
    start = false;
}

/**
 * @name handleInput
 * @brief Handles user input for the Game Intro stage, starting the game on space or return key press
 * We have to handle at the game level if the key was previously pressed to avoid multiple triggers.
 * Basically, pressing enter or space on game over will route here, which also uses space/enter to start the game,
 * they can both trigger at the same time, so have to introduce a "pause"
 * @param state Current keyboard state
 * @memberof GameIntroStage
 */
void GameIntroStage::handleInput(const Uint8* state) {
    bool spacePressed = state[SDL_SCANCODE_SPACE] && !game->spaceWasPressed;
    bool returnPressed = state[SDL_SCANCODE_RETURN] && !game->returnWasPressed;

    if (spacePressed || returnPressed) {
        printf("Starting game...\n");
        start = true;
    }
}

/**
 * @name update
 * @brief Updates the Game Intro stage, animating the background and transitioning to gameplay on start
 * @param deltaTime Time elapsed since last frame
 * @return StageType - Next stage to transition to, or NONE if no transition
 * @memberof GameIntroStage
 */
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

/**
 * @name draw
 * @brief Renders the Game Intro stage to the screen
 * @memberof GameIntroStage
 */
void GameIntroStage::draw() {
    drawBackground();
    drawBase();
    drawIntro();
}

/**
 * @name drawIntro
 * @brief Draws the intro message texture at the center of the screen
 * @memberof GameIntroStage
 */
void GameIntroStage::drawIntro() {
    blit(game->app, gameIntroTexture,
        SCREEN_WIDTH / 2 - (gameIntroTextureWidth / 2),  backgroundY, 0, SDL_FLIP_NONE);
}

/**
 * @name drawBackground
 * @brief Draws the scrolling background texture
 * @memberof GameIntroStage
 */
void GameIntroStage::drawBackground() {
    for (double x = backgroundX; x < SCREEN_WIDTH; x += SCREEN_WIDTH) {
        blit(game->app, background, x, 0);
    }
}

/**
 * @name drawBase
 * @brief Draws the scrolling base texture at the bottom of the screen
 * @memberof GameIntroStage
 */
void GameIntroStage::drawBase() {
    for (double x = baseX; x < SCREEN_WIDTH; x += SCREEN_WIDTH) {
        blit(game->app, base, x, SCREEN_HEIGHT - BASE_HEIGHT);
    }
}

