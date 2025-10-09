//
// Created by Hayden Beadles on 10/5/25.
//

#ifndef FLAPPY_BIRD_SDL2_STAGE_H
#define FLAPPY_BIRD_SDL2_STAGE_H
#include <common.h>

// Forward declaration to avoid circular dependency
class Game;

class Stage {
public:
    Stage(Game *game, StageType type);
    virtual ~Stage() = default;
    virtual void init();
    virtual void handleInput(const Uint8* state);
    virtual StageType update(float deltaTime);
    virtual void reset();
    bool hasPipeManager();

    virtual void draw();
    StageType getType() const;
protected:
    Game* game;
private:
    StageType type;
};
#endif //FLAPPY_BIRD_SDL2_STAGE_H