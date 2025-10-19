//
// Created by Hayden Beadles on 10/5/25.
//
#ifndef FLAPPY_BIRD_SDL2_FLAPPY_BIRD_STAGE_H
#define FLAPPY_BIRD_SDL2_FLAPPY_BIRD_STAGE_H
#include <game/stage.h>
#include <system/common.h>

/**
 * @name FlappyBirdStage
 * @class FlappyBirdStage
 * @brief Stage for the main gameplay of Flappy Bird. Extends Stage class.
 */
class FlappyBirdStage : public Stage {
public:
    explicit FlappyBirdStage(Game *game);
    ~FlappyBirdStage() override = default;
    void init() override;
    void handleInput(const Uint8* state) override;
    StageType update(float deltaTime) override;
    void reset() override;
    void draw() override;
private:
    void drawBackground();
    void drawBase();
    SDL_Texture* background;
    SDL_Texture* base;
    double backgroundX;
    double baseX;
    int gameOverTimer = FPS * 2;
};


#endif //FLAPPY_BIRD_SDL2_FLAPPY_BIRD_STAGE_H