//
// Created by Hayden Beadles on 10/5/25.
//

#ifndef FLAPPY_BIRD_SDL2_FLAPPY_BIRD_STAGE_H
#define FLAPPY_BIRD_SDL2_FLAPPY_BIRD_STAGE_H
#include <game/stage.h>
#include <system/common.h>
#include <draw/text.h>

class FlappyBirdStage : public Stage {
public:
    FlappyBirdStage(Game *game);
    virtual ~FlappyBirdStage() = default;
    virtual void init() override;
    virtual void handleInput(const Uint8* state) override;
    virtual StageType update(float deltaTime) override;
    virtual void reset() override;
    virtual void draw() override;
private:
    Text textWriter;
    void drawBackground();
    void drawBase();
    SDL_Texture* background;
    SDL_Texture* base;
    double backgroundX;
    double baseX;
    int gameOverTimer = FPS * 3;
};


#endif //FLAPPY_BIRD_SDL2_FLAPPY_BIRD_STAGE_H