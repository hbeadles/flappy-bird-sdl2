//
// Created by Hayden Beadles on 10/9/25.
//

#ifndef FLAPPY_BIRD_SDL2_GAMEINTRO_H
#define FLAPPY_BIRD_SDL2_GAMEINTRO_H
#include <game/stage.h>
#include <system/common.h>

class GameIntroStage : public Stage {
public:
    GameIntroStage(Game *game);
    virtual ~GameIntroStage() = default;
    virtual void init() override;
    virtual void handleInput(const Uint8* state) override;
    virtual StageType update(float deltaTime) override;
    virtual void reset() override;

    virtual void draw() override;
private:
    bool start=false;
    void drawBackground();
    void drawIntro();
    void drawBase();
    SDL_Texture* background;
    SDL_Texture* base;
    SDL_Texture* gameIntroTexture;
    int gameIntroTextureWidth;
    int gameIntroTextureHeight;
    double backgroundX;
    double backgroundY;
    double baseX;
};
#endif //FLAPPY_BIRD_SDL2_GAMEINTRO_H