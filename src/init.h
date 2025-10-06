//
// Created by Hayden Beadles on 10/5/25.
//

#ifndef FLAPPY_BIRD_SDL2_INIT_H
#define FLAPPY_BIRD_SDL2_INIT_H
#include <common.h>

/**
 * @file init.h
 * @brief Header file for SDL initialization and cleanup functions.
 * @author Hayden Beadles
 */


bool initSDL(Application &app, const std::string& title);
void cleanup(Application &app);


#endif //FLAPPY_BIRD_SDL2_INIT_H