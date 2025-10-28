//
// Created by Hayden Beadles on 10/8/25.
//

#ifndef FLAPPY_BIRD_SDL2_UTILS_H
#define FLAPPY_BIRD_SDL2_UTILS_H
#include <system/common.h>

CollisionSide getCollisionSide(Flappy *a, Pipe *b);
bool checkCollisionRect(const SDL_Rect& a, const SDL_Rect& b);
bool collision(Flappy *a, Pipe *b);
double distance(SDL_Point a, SDL_Point b);
double verticalDistance(SDL_Point a, SDL_Point b);
double angleBetweenPoints(SDL_Point a, SDL_Point b);
bool aBelowB(SDL_Point a, SDL_Point b);
#endif //FLAPPY_BIRD_SDL2_UTILS_H