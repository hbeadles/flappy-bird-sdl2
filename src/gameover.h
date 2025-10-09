//
// Created by Hayden Beadles on 10/8/25.
//

#ifndef FLAPPY_BIRD_SDL2_GAMEOVER_H
#define FLAPPY_BIRD_SDL2_GAMEOVER_H
#include <stage.h>
#include <common.h>

class GameOverStage : public Stage {
public:
    GameOverStage(Game *game);
    virtual ~GameOverStage() = default;
    virtual void init() override;
    virtual void handleInput(const Uint8* state) override;
    virtual StageType update(float deltaTime) override;
    virtual void reset() override;

    virtual void draw() override;
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