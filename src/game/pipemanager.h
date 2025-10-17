//
// Created by Hayden Beadles on 10/8/25.
//

#ifndef FLAPPY_BIRD_SDL2_PIPE_H
#define FLAPPY_BIRD_SDL2_PIPE_H
#include <system/common.h>

class Game;

/**
 * @name PipeManager
 * @class PipeManager
 * @brief Manages a set of pipes for the Flappy Bird game
 */
class PipeManager {
public:
    explicit PipeManager(Game* game);
    void initPipes();
    void updatePipes(Flappy * flappy, float deltaTime);
    void drawPipes();
    void clearPipes();
    std::vector<Pipe> pipePool;
private:
    Game* game;
    void generatePipePair(float& topY, float& bottomY, float &gap);
    bool containsInactivePipe(bool isTop);
    float randomFloat(float min, float max);
    AtlasImage* pipeTexture = nullptr;
    const int TOTAL_PIPES = 8;
    const int G_MIN = 70;
    const int G_MAX = 100;
    float gap_fraction = 0.5f;
    float gap_height;
    float bottomGapMax;
    float topGapMax;
    const int PIPE_HORIZONTAL_GAP = 200;
    const int PIPE_HEIGHT = 320;
    const float PIPE_SCROLL_SPEED = 2.0f; // 60 pixels per second
    const float PIPE_SPAWN_INTERVAL = PIPE_HORIZONTAL_GAP / (PIPE_SCROLL_SPEED * 1.1); // seconds between spawns
    float spawnTimer = 0.0f;
};
#endif //FLAPPY_BIRD_SDL2_PIPE_H