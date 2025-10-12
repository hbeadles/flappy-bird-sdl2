//
// Created by Hayden Beadles on 10/8/25.
//

#ifndef FLAPPY_BIRD_SDL2_GAMEOVER_H
#define FLAPPY_BIRD_SDL2_GAMEOVER_H
#include <game/stage.h>
#include <system/common.h>

/**
 * @name GameOverStage
 * @class GameOverStage
 * @brief Stage for the Game Over screen in Flappy Bird. Extends Stage class.
 */
class GameOverStage : public Stage {
public:
    explicit GameOverStage(Game *game);
    ~GameOverStage() override = default;
    void init() override;
    void handleInput(const Uint8* state) override;
    StageType update(float deltaTime) override;
    void reset() override;

    void draw() override;
private:
    bool restart=false;
    void drawBackground();
    void drawGameOver();
    void drawBase();
    SDL_Texture* background;
    SDL_Texture* base;
    SDL_Texture* gameOverTexture;
    int gameOverTextureWidth;
    int gameOverTextureHeight;
    double backgroundX;
    double backgroundY;
    double baseX;
};
#endif //FLAPPY_BIRD_SDL2_GAMEOVER_H