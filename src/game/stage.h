//
// Created by Hayden Beadles on 10/5/25.
//

#ifndef FLAPPY_BIRD_SDL2_STAGE_H
#define FLAPPY_BIRD_SDL2_STAGE_H
#include <system/common.h>

// Forward declaration to avoid circular dependency
class Game;

/**
 * @name Stage
 * @class Stage
 * @brief Base class for different stages of Flappy Bird
 */
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
    [[nodiscard]] StageType getType() const;
protected:
    Game* game;
private:
    StageType type;
};
#endif //FLAPPY_BIRD_SDL2_STAGE_H