//
// Created by Hayden Beadles on 10/5/25.
//

#ifndef FLAPPY_BIRD_SDL2_DEFS_H
#define FLAPPY_BIRD_SDL2_DEFS_H
#define FLAPPY_MAX_ROTATION 90.0f
#define FLAPPY_ROTATION_SPEED 150.0f
#define SCREEN_WIDTH 288
#define SCREEN_HEIGHT 512
#define GRAVITY .2f
#define BASE_HEIGHT 112
#define MAX_SND_CHANNELS 8
#define FPS 60

enum {
    ET_FLAPPY_BIRD,
    ET_PIPE
};

enum CollisionSide{
    SIDE_NONE,
    SIDE_TOP,
    SIDE_BOTTOM,
    SIDE_LEFT,
    SIDE_RIGHT
};

// Stage types for the game state machine
enum class StageType {
    NONE,
    GAMEPLAY,
    GAME_OVER,
    // Future stages can be added here:
    // MAIN_MENU,
    // PAUSE,
    // SETTINGS,
    // etc.
};

// enum class StageTransitionEvent {
//     NONE = 0,
//     TO_GAMEPLAY = 1,
//     TO_GAME_OVER = 2,
//     // TO_MAIN_MENU = 3,
//     // TO_PAUSE = 4,
//     // RESTART_GAME = 5
// };
#endif //FLAPPY_BIRD_SDL2_DEFS_H