//
// Created by Hayden Beadles on 10/24/25.
//

#ifndef FLAPPY_BIRD_SDL2_FLAPPY_BIRD_AI_H
#define FLAPPY_BIRD_SDL2_FLAPPY_BIRD_AI_H
#include <system/common.h>
#include <game/pipemanager.h>
#include <draw/draw.h>

class Game;

enum FlappyAIStates {
    IDLE,
    FLAPPING
};

class FlappyAI {
public:
    FlappyAI(Game * game);

    void update(Flappy* flappy, PipeManager* pipeManager, float deltaTime);
    void draw(Flappy* flappy);
    void reset();
    bool enabled = false;
private:
    Game* game;
    std::vector<SDL_Point> calculateMidPoints(Flappy* flappy, PipeManager* pipeManager);

    FlappyAIStates mState;
    std::vector<SDL_Point> pipeMidPoints;
};

#endif //FLAPPY_BIRD_SDL2_FLAPPY_BIRD_AI_H