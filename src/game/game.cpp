//
// Created by Hayden Beadles on 10/5/25.
//
#include <game/game.h>
#include <game/stage.h>
#include <system/init.h>
#include <game/flappy_bird_stage.h>
#include <draw/draw.h>
#include <system/atlas.h>
#include <utils/utils.h>
#include <game/gameover.h>
#include <game/gameintro.h>

/**
 * @name Game
 * @brief Constructor for Game class, sets up initial objects
 * @param app Application struct reference
 * @memberof Game
 */
Game::Game(Application &app): app(app), pipe_manager(nullptr) {
    std::srand(std::time(nullptr));  // Initialize random seed
    app.screenHeight = SCREEN_HEIGHT;
    app.screenWidth = SCREEN_WIDTH;
    this->mIsRunning = true;
    this->mTicksCount = 0;
    this->score = 0;
    pipe_manager = std::make_unique<PipeManager>(this);
}

Game::~Game() {

}

/**
 * @name initialize
 * @brief Initializes SDL, Atlas and stages
 * @param title Title of the game window
 * @return True if initialization was successful, false otherwise
 * @memberof Game
 */
bool Game::initialize(const std::string& title) {
    bool init = initSDL(app, title);
    initAtlas(app);
    stages[StageType::GAME_INTRO] = std::make_unique<GameIntroStage>(this);
    stages[StageType::GAMEPLAY] = std::make_unique<FlappyBirdStage>(this);
    stages[StageType::GAME_OVER] = std::make_unique<GameOverStage>(this);
    for (auto& [type, stage] : stages) {
        stage->init();
    }
    transitionToStage(StageType::GAME_INTRO);

    return init;
};

/**
 * @name initFlappy
 * @brief Initializes the Flappy character with textures and properties
 * @memberof Game
 */
void Game::initFlappy() {
    flappy = std::make_unique<Flappy>();
    flappy->idleTexture = getAtlasImage(app,  "gfx/yellowbird-01.png");
    if (flappy->jumpTextures.empty()){
        for (int i = 0; i < 3; i++){
            std::string filename =  "gfx/yellowbird-0" + std::to_string(i + 1) + ".png";
            AtlasImage* texture = getAtlasImage(app, filename);
            flappy->jumpTextures.push_back(texture);
        }
    }
    // flappy->jumpAnimation = new Animation();
    // flappy->jumpAnimation->name = "jump";
    flappy->jumpAngle = 0.0f;
    flappy->x = 100.0f;
    flappy->y = 100.0f;
    flappy->dx = 0.0f;
    flappy->dy = 0.0f;
    flappy->health = 1;
    flappy->active = true;
    flappy->isJumping = false;

}

/**
 * @name handleFlappy
 * @brief Handles input for the Flappy character
 * @param state Current keyboard state
 * @memberof Game
 */
void Game::handleFlappy(const Uint8 *state) {
    if (state[SDL_SCANCODE_SPACE] && flappy->active) {
        currentState = JUMP;
    }else {
        currentState = FALL;
    }
}

/**
 * @name updateFlappy
 * @brief Updates the Flappy character position and animation, if jumping
 * @param deltaTime Time elapsed since last frame
 * @memberof Game
 */
void Game::updateFlappy(float deltaTime) {

    flappy->y += flappy->dy * deltaTime;
    flappy->x += flappy->dx * deltaTime;
    flappy->dy += GRAVITY * 60.0f;

    float targetRotation = flappy->dy * FLAPPY_ROTATION_SPEED * deltaTime;
    targetRotation = std::clamp(targetRotation, -35.0f, FLAPPY_MAX_ROTATION);
    flappy->jumpAngle = targetRotation;

    if (currentState == JUMP && flappy->active) {
        flappy->dy = -125.0f;
        flappy->jumpAngle = -35.0f;
        if (!flappy->isJumping) {
            flappy->isJumping = true;
            flappy->animTimer = 0.0f;
            flappy->currentFrame = 0;
        }
    }
    if (flappy->active) {
        for (Pipe& pipe : pipe_manager->pipePool){
            if (pipe.active && collision(flappy.get(), &pipe)){
                CollisionSide side = getCollisionSide(flappy.get(), &pipe);
                if (flappy->active) {
                    //playSound("hit");
                }
                switch(side) {
                    case SIDE_TOP:
                        // Bird hit top of pipe - bounce up
                        flappy->dy = -abs(flappy->dy);
                        flappy->y = pipe.y - flappy->idleTexture->rect.h - 1;

                        break;
                    case SIDE_BOTTOM:
                        // Bird hit bottom of pipe - bounce down
                        flappy->dy = abs(flappy->dy);
                        flappy->y = pipe.y + pipe.texture->rect.h + 1;
                        break;
                    case SIDE_LEFT:
                        // Bird hit left side of pipe - bounce left
                        flappy->dx = -abs(flappy->dx);
                        flappy->x = pipe.x - flappy->idleTexture->rect.w - 1;
                        break;
                    case SIDE_RIGHT:
                        // Bird hit right side of pipe - bounce right
                        flappy->dx = abs(flappy->dx);
                        flappy->x = pipe.x + pipe.texture->rect.w + 1;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    if (flappy->y < 0.0f) {
        flappy->health--;
    }
    if (flappy->y > (SCREEN_HEIGHT - BASE_HEIGHT - flappy->idleTexture->rect.h)) {
        flappy->health--;
        flappy->y = SCREEN_HEIGHT - BASE_HEIGHT - flappy->idleTexture->rect.h;
    }
    if (flappy->x < 0.0f) {
        flappy->health--;
        flappy->x = 0.0f;
    }
    if (flappy->x > SCREEN_WIDTH) {
        flappy->health--;
        flappy->x = SCREEN_WIDTH;
    }

    if (flappy->health <= 0){
        flappy->active = false;
    }

    if (flappy->isJumping) {
        flappy->animTimer += deltaTime;
        if (flappy->animTimer >= flappy->frameTime) {
            flappy->animTimer = 0.0f;
            flappy->currentFrame++;
            if (flappy->currentFrame >= flappy->jumpTextures.size()) {
                flappy->currentFrame = 0;
                flappy->isJumping = false;
            }
        }
    }


}

/**
 * @name renderFlappy
 * @brief Renders the Flappy character on screen. Handles if its jumping or not
 * @memberof Game
 */
void Game::renderFlappy() {
    if (flappy->isJumping) {
        blitAtlasImage(app,
            flappy->jumpTextures[flappy->currentFrame],
            flappy->x,
            flappy->y,
            0,
            flappy->jumpAngle,
            SDL_FLIP_NONE);
    }else {
        blitAtlasImage(app,
            flappy->idleTexture,
            flappy->x,
            flappy->y,
            0,
            flappy->jumpAngle,
            SDL_FLIP_NONE);
    }
}


/**
 * @name transitionToStage
 * @brief Transitions the game to a new stage, initializing it as needed. This is the function we
 * use to allow stages to communicate with the Game class. It's not the best way, but it works.
 * (Why its not ideal) - It ties Game to the stages, making them less separable.
 * @param stageType The type of stage to transition to
 * @memberof Game
 */
void Game::transitionToStage(StageType stageType) {
    if (currentStage) {
        //currentStage->cleanup();
    }
    currentStage = stages[stageType].get();
    if (stageType == StageType::GAME_INTRO) {
        currentStage->reset();
        currentStage->init();
        flappy = nullptr;
    }
    if (stageType == StageType::GAMEPLAY){
        currentStage->reset();
        currentStage->init();
        initFlappy();
    }
    if (stageType == StageType::GAME_OVER) {
        currentStage->reset();
        currentStage->init();
    }
}

/**
 * @name runloop
 * @brief Main game loop, processes input, updates game state, and renders output
 * @memberof Game
 */
void Game::runloop(){
    while(mIsRunning){
        processInput();
        updateGame();
        generateOutput();
    }
};

/**
 * @name processInput
 * @brief Processes user input events and updates game state accordingly
 * @memberof Game
 */
void Game::processInput() {

    SDL_Event event;
    while(SDL_PollEvent(&event)){

        switch(event.type){
            case SDL_QUIT:
                mIsRunning = false;
#ifdef __EMSCRIPTEN__
                emscripten_cancel_main_loop();
#endif
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                        app.screenWidth = event.window.data1;
                        app.screenHeight = event.window.data2;
                        break;
                default: ;
                }
            default: ;
        }

    }

    const Uint8* state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_ESCAPE]){
        mIsRunning = false;
#ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
#endif
    }

    if (currentStage) {
        currentStage->handleInput(state);
    }
    if (flappy != nullptr) {
        handleFlappy(state);
    }

    spaceWasPressed = state[SDL_SCANCODE_SPACE];
    returnWasPressed = state[SDL_SCANCODE_RETURN];
};

/**
 * @name updateGame
 * @brief Updates the game state, class Stage updates and Flappy character updates if they exist
 * @memberof Game
 */
void Game::updateGame() {
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f){
        deltaTime = 0.05f;
    }
    mTicksCount = SDL_GetTicks();

    if (currentStage) {
        StageType nextStage = currentStage->update(deltaTime);
        if (nextStage != StageType::NONE) {
            transitionToStage(nextStage);
        }
    }
    if (flappy != nullptr) {
        updateFlappy(deltaTime);
    }
};

/**
 * @name generateOutput
 * @brief Renders the current game state to the screen
 * @memberof Game
 */
void Game::generateOutput(){
    prepareScene(app);
    if (currentStage) {
        currentStage->draw();
    }
    if (flappy != nullptr) {
        renderFlappy();
    }
    presentScene(app);
}

/**
 * @name shutdown
 * @brief Cleans up resources and shuts down the game
 * @memberof Game
 */
void Game::shutdown(){
    cleanup(app);
}

