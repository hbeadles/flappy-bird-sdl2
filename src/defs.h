//
// Created by Hayden Beadles on 10/5/25.
//

#ifndef FLAPPY_BIRD_SDL2_DEFS_H
#define FLAPPY_BIRD_SDL2_DEFS_H

#define SCREEN_WIDTH 288
#define SCREEN_HEIGHT 512
#define GRAVITY .2f
#define BASE_HEIGHT 112

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

#endif //FLAPPY_BIRD_SDL2_DEFS_H