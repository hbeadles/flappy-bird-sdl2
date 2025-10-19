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
                                             flappyBirdText(nullptr),
                                             gameStartText(nullptr),
                                             flappyBirdRect(nullptr),
                                             backgroundX(0),
                                             backgroundY(0),
                                             baseX(0),
                                             gameStartTextWidth(0),
                                             gameStartTextHeight(0) {
}

/**
 * @name init
 * @brief Initializes the Game Intro stage, loading textures and setting initial positions
 * @memberof GameIntroStage
 */
void GameIntroStage::init() {
    background = loadTexture(game->app, "gfx/background-2.png");
    colorModulate(background, 200, 200, 200);
    base = loadTexture(game->app, "gfx/base_dark_large.png");
    flappyBirdText = loadTextTexture(game->app, "Flappy Bird",
        {255, 191, 0}, game->textWriter.getFont());
    gameStartText = loadTextTexture(game->app, "Game Start",
        {205, 127, 50}, game->textWriter.getFont());

    SDL_QueryTexture(flappyBirdText, NULL, NULL, &flappyBirdTextWidth, &flappyBirdTextHeight);
    SDL_QueryTexture(gameStartText, NULL, NULL, &gameStartTextWidth, &gameStartTextHeight);
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
    if (backgroundY >= (SCREEN_HEIGHT / 2 - flappyBirdTextHeight * 2.5)) {
        backgroundY = (SCREEN_HEIGHT / 2 - flappyBirdTextHeight * 2.5);
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
    blit(game->app, flappyBirdText,
        SCREEN_WIDTH / 2 - (flappyBirdTextWidth / 2),  backgroundY, 0, SDL_FLIP_NONE);
    blit(game->app, gameStartText,
        SCREEN_WIDTH / 2 - (gameStartTextWidth / 2),  backgroundY + flappyBirdTextHeight + 20, 0, SDL_FLIP_NONE);
}

/**
 * @name drawBackground
 * @brief Draws the scrolling background texture
 * @memberof GameIntroStage
 */
void GameIntroStage::drawBackground() {
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
 * @memberof GameIntroStage
 */
void GameIntroStage::drawBase() {
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

