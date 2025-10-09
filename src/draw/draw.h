#ifndef FLAPPY_BIRD_SDL2_DRAW_H
#define FLAPPY_BIRD_SDL2_DRAW_H
#include <system/common.h>

void prepareScene(Application & app);
void presentScene(Application & app);
void blit(Application & app, SDL_Texture * texture, int x, int y, double angle =0, SDL_RendererFlip flip = SDL_FLIP_NONE);
void blitAtlasImage(Application & app, AtlasImage * image, int x, int y, int center, double angle =0, SDL_RendererFlip flip = SDL_FLIP_NONE);

#endif