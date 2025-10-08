//
// Created by Hayden Beadles on 10/5/25.
//
#include <game.h>
#include <stage.h>
#include <init.h>
#include <flappy_bird_stage.h>
#include <draw.h>
#include <atlas.h>
#include <atlas.h>

Game::Game(Application &app){
    std::srand(std::time(nullptr));  // Initialize random seed
    app.screenHeight = SCREEN_HEIGHT;
    app.screenWidth = SCREEN_WIDTH;
    this->app = app;
    this->mIsRunning = true;
    this->mTicksCount = 0;
    this->score = 0;
};

Game::~Game() {

}

bool Game::initialize(const std::string& title) {
    bool init = initSDL(app, title);
    stages[StageType::GAMEPLAY] = std::make_unique<FlappyBirdStage>(this);
    for (auto& [type, stage] : stages) {
        stage->init();
    }
    initAtlas(app);
    initFlappy();
    transitionToStage(StageType::GAMEPLAY);

    return init;
};

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

void Game::handleFlappy(const Uint8 *state) {
    if (state[SDL_SCANCODE_SPACE]) {
        currentState = JUMP;
    }else {
        currentState = FALL;
    }
}

void Game::updateFlappy(float deltaTime) {
    if (!flappy->active) {
        return;
    }
    flappy->y += flappy->dy * deltaTime;
    flappy->x += flappy->dx * deltaTime;

    float targetRotation = flappy->dy * FLAPPY_ROTATION_SPEED * deltaTime;
    targetRotation = std::clamp(targetRotation, -35.0f, FLAPPY_MAX_ROTATION);
    flappy->jumpAngle = targetRotation;

    if (currentState == JUMP) {
        flappy->dy = -125.0f;
        flappy->jumpAngle = -35.0f;
        if (!flappy->isJumping) {
            flappy->isJumping = true;
            flappy->animTimer = 0.0f;
            flappy->currentFrame = 0;
        }
    }else {
        flappy->dy += GRAVITY * 30.0f;
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

void Game::renderFlappy() {
    if (flappy->isJumping) {
        blitAtlasImage(app, flappy->jumpTextures[flappy->currentFrame], flappy->x, flappy->y, 0, flappy->jumpAngle, SDL_FLIP_NONE);
    }else {
        blitAtlasImage(app, flappy->idleTexture, flappy->x, flappy->y, 0, flappy->jumpAngle, SDL_FLIP_NONE);
    }
}



void Game::transitionToStage(StageType stageType) {
    if (currentStage) {
        //currentStage->cleanup();
    }
    currentStage = stages[stageType].get();
    if (stageType == StageType::GAMEPLAY){
        initFlappy();
    }
    currentStage->reset();
}

void Game::runloop(){
    while(mIsRunning){
        processInput();
        updateGame();
        generateOutput();
    }
};

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
    handleFlappy(state);
};

void Game::updateGame() {
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f){
        deltaTime = 0.05f;
    }
    bool windowPointer = true;
    mTicksCount = SDL_GetTicks();

    if (currentStage) {
        StageType nextStage = currentStage->update(deltaTime);
        if (nextStage != StageType::NONE) {
            transitionToStage(nextStage);
        }
    }
    updateFlappy(deltaTime);
};

void Game::generateOutput(){
    prepareScene(app);
    if (currentStage) {
        currentStage->draw();
    }
    renderFlappy();
    presentScene(app);
}

void Game::shutdown(){
    cleanup(app);
}

