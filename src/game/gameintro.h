//
// Created by Hayden Beadles on 10/9/25.
//

#ifndef FLAPPY_BIRD_SDL2_GAMEINTRO_H
#define FLAPPY_BIRD_SDL2_GAMEINTRO_H
#include <game/stage.h>
#include <system/common.h>

/**
 * @name GameIntroStage
 * @class GameIntroStage
 * @brief Stage for the Game Intro screen in Flappy Bird. Extends Stage class.
 */
class GameIntroStage : public Stage {
public:
    explicit GameIntroStage(Game *game);
    ~GameIntroStage() override = default;
    void init() override;
    void handleInput(const Uint8* state) override;
    StageType update(float deltaTime) override;
    void reset() override;

    void draw() override;
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