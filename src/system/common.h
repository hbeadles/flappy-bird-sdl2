//
// Created by Hayden Beadles on 10/5/25.
//

#ifndef FLAPPY_BIRD_SDL2_COMMON_H
#define FLAPPY_BIRD_SDL2_COMMON_H
#include "SDL2/SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <system/defs.h>
#include <string>
#include <cstdio>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <system/structs.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif
#endif //FLAPPY_BIRD_SDL2_COMMON_H