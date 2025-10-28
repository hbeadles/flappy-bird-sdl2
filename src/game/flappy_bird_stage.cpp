//
// Created by Hayden Beadles on 10/5/25.
//
#include <game/flappy_bird_stage.h>
#include <game/game.h>
#include <draw/textures.h>
#include <draw/draw.h>

/**
 * @name FlappyBirdStage
 * @brief Constructor for FlappyBirdStage class
 * @memberof FlappyBirdStage
 * @param game
 */
FlappyBirdStage::FlappyBirdStage(Game *game)
    : Stage(game, StageType::GAMEPLAY),
      background(nullptr),
      base(nullptr),
      backgroundX(0),
      baseX(0) {
};

/**
 * @name init
 * @brief Sets up Flappy Bird main game textures. Sets up pipe manager
 * @memberof FlappyBirdStage
 */
void FlappyBirdStage::init() {
    background = loadTexture(game->app, "gfx/background-2.png");
    colorModulate(background, 200, 200, 200);
    base = loadTexture(game->app, "gfx/base_dark_large.png");
    if (hasPipeManager()) {
        game->pipe_manager->initPipes();
    }
};

/**
 * @name reset
 * @brief Resets the Flappy Bird stage to initial state
 * @memberof FlappyBirdStage
 */
void FlappyBirdStage::reset() {
    backgroundX = 0;
    baseX = 0;
    game->score = 0;
    if (hasPipeManager()){
        game->pipe_manager->clearPipes();
    }
};

/**
 * @name update
 * @brief Updates the Flappy Bird stage each frame
 * @memberof FlappyBirdStage
 * @param deltaTime
 * @return StageType - Are we transitioning? Return the stage if so, else None
 */
StageType FlappyBirdStage::update(float deltaTime) {
    backgroundX -= deltaTime * 50;

    if (backgroundX <= -SCREEN_WIDTH) {
        backgroundX = 0;
    }
    baseX -= (deltaTime * 100);
    if (baseX <= -SCREEN_WIDTH) {
        baseX = 0;
    }

    if (hasPipeManager()) {
        game->pipe_manager->updatePipes(game->flappy.get(), deltaTime);
    }
    if (game->flappy && game->flappy->active == false) {
        gameOverTimer--;
        if (gameOverTimer <= 0) {
            printf("Game over. Restarting...\n");
            gameOverTimer = FPS * 3;
            return StageType::GAME_OVER;
        }
    }
   // flappyAI->update(game->flappy.get(), game->pipe_manager.get(), deltaTime);
    return StageType::NONE;
}

/**
 * @name drawAIControls
 * @brief Draws AI control UI (stop button) in bottom right corner
 * @memberof FlappyBirdStage
 */
void FlappyBirdStage::drawAIControls() {
    if (!game->use_flappy_ai) {
        return;
    }

    // Style the stop button
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(16, 10)); // Add padding for the button
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // Remove window padding

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));        // Red
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.3f, 0.3f, 1.0f)); // Lighter red on hover
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.1f, 0.1f, 1.0f));  // Darker red when pressed
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));         // White text

    // Position in bottom right
    ImVec2 buttonSize(100, 40);  // Increased size to fit text
    float padding = 10.0f;
    int offsetX = (game->app.screenWidth - BACKGROUND_WIDTH) / 2;
    int offsetY = (game->app.screenHeight - BACKGROUND_HEIGHT) / 2;

    ImVec2 windowPos((offsetX + SCREEN_WIDTH - buttonSize.x - padding), (offsetY + SCREEN_HEIGHT - buttonSize.y - padding));

    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(buttonSize.x + 20, buttonSize.y + 20), ImGuiCond_Always);

    ImGui::Begin("AIControls", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoBackground);

    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - buttonSize.x) * 0.5f);

    if (ImGui::Button("Stop AI", buttonSize)) {
        printf("Stopping AI...\n");
        game->flappy->active = false;
        // Optionally return to menu or switch to player control
        // transitionToStage(StageType::GAME_INTRO);
    }

    ImGui::End();

    ImGui::PopStyleColor(4);
    ImGui::PopStyleVar(3);
}


/**
 * @name draw
 * @brief Draws the Flappy Bird stage each frame
 * @memberof FlappyBirdStage
 */
void FlappyBirdStage::draw() {

    drawBackground();
    if (hasPipeManager()) {
        game->pipe_manager->drawPipes();
    }
    drawBase();
    int offsetY = BACKGROUND_HEIGHT - SCREEN_HEIGHT ;
    game->textWriter.drawScore(game->score, (SCREEN_WIDTH / 2) - 24, offsetY);
    drawAIControls();
}

/**
 * @name drawBackground
 * @brief Draws the scrolling background
 * @memberof FlappyBirdStage
 */
void FlappyBirdStage::drawBackground() {
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
        //blit(game->app, background, x, 0, 45.0);
    }
}

/**
 * @name drawBase
 * @brief Draws the scrolling base
 * @memberof FlappyBirdStage
 */
void FlappyBirdStage::drawBase() {
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

void FlappyBirdStage::handleInput(const Uint8* state) {

}