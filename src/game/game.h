//
// Created by Hayden Beadles on 10/5/25.
//

#ifndef FLAPPY_BIRD_SDL2_GAME_H
#define FLAPPY_BIRD_SDL2_GAME_H
#include <system/common.h>
#include <draw/text.h>
#include <game/pipemanager.h>

// Forward declaration to avoid circular dependency
class Stage;
/**
 * @class Game
 * @name Game
 * @brief High level Game class, handles main loop, input processing, game updates, and rendering.
 */
class Game{

public:
    explicit Game(Application & app);
    ~Game(); // Declare destructor in header
    bool initialize(const std::string& title);
    void runloop();
    void shutdown();
    Application& app;
    void processInput();
    void updateGame();
    void generateOutput();
    void initFlappy();

    void handleFlappy(const Uint8* state);
    void updateFlappy(float deltaTime);
    void renderFlappy();
    bool mIsRunning;
    double score;
    void transitionToStage(StageType stageType);
    std::unique_ptr<PipeManager> pipe_manager;
    std::unique_ptr<Flappy> flappy=nullptr;
    bool spaceWasPressed = false;
    bool returnWasPressed = false;
    Text textWriter;

    float cameraRotation = 0.0f;
    SDL_Point cameraCenter = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
private:
    std::unordered_map<StageType, std::unique_ptr<Stage>> stages;
    Stage* currentStage = nullptr;
    SDL_Window* mWindow{};
    SDL_Renderer* mRenderer{};
    Uint32 mTicksCount;
    enum FlappyState {
        JUMP,
        FALL
    };
    FlappyState currentState = FALL;
};


#endif //FLAPPY_BIRD_SDL2_GAME_H