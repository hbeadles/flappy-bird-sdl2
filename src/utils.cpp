//
// Created by Hayden Beadles on 10/8/25.
//
#include <utils.h>

bool collision(Flappy *a, Pipe *b){
    SDL_Rect aRect = {(int)a->x, (int)a->y, a->idleTexture->rect.w, a->idleTexture->rect.h};
    SDL_Rect bRect = {(int)b->x, (int)b->y, b->texture->rect.w, b->texture->rect.h};
    return checkCollisionRect(aRect, bRect);
}
bool checkCollisionRect(const SDL_Rect& a, const SDL_Rect& b){
    return SDL_HasIntersection(&a, &b);
}

CollisionSide getCollisionSide(Flappy *a, Pipe *b){
    SDL_Rect aRect = {
        (int)a->x,
        (int)a->y,
        a->idleTexture->rect.w,
        a->idleTexture->rect.h
    };
    SDL_Rect bRect = {
        (int)b->x,
        (int)b->y,
        b->texture->rect.w,
        b->texture->rect.h
    };
    if (checkCollisionRect(aRect, bRect)){
        // Calculate overlap distances
        int overlap_left = (aRect.x + aRect.w) - bRect.x;
        int overlap_right = (bRect.x + bRect.w) - aRect.x;
        int overlap_top = (aRect.y + aRect.h) - bRect.y;
        int overlap_bottom = (bRect.y + bRect.h) - aRect.y;

        if (b->isTop) {
            if (overlap_bottom <= overlap_left && overlap_bottom <= overlap_right && overlap_bottom <= overlap_top) {
                return SIDE_BOTTOM;
            }
            if (overlap_left <= overlap_right && overlap_left <= overlap_top) {
                return SIDE_LEFT;
            }
            if (overlap_right <= overlap_top) {
                return SIDE_RIGHT;
            }
            return SIDE_TOP;
        }
        // For bottom
        if (overlap_top <= overlap_left && overlap_top <= overlap_right && overlap_top <= overlap_bottom) {
            return SIDE_TOP;
        }
        if (overlap_left <= overlap_right && overlap_left <= overlap_bottom) {
            return SIDE_LEFT;
        }
        if (overlap_right <= overlap_bottom) {
            return SIDE_RIGHT;
        }
        return SIDE_BOTTOM;
    }
    return SIDE_NONE;

}