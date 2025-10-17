//
// Created by Hayden Beadles on 10/5/25.
//

#ifndef FLAPPY_BIRD_SDL2_TEXTURES_H
#define FLAPPY_BIRD_SDL2_TEXTURES_H
#include <system/common.h>
SDL_Texture *toTexture(SDL_Surface *surface, int destroySurface);
SDL_Texture* loadTexture(Application & app, const std::string & filename);
SDL_Texture* loadTextureWithColorKey(Application & app, std::string filename, Uint8 r, Uint8 g, Uint8 b);
SDL_Texture* getTexture(Application & app, const std::string & filename);
SDL_Texture* loadTextTexture(Application & app,
    const std::string & text,
    SDL_Color color,
    TTF_Font* font);
#endif //FLAPPY_BIRD_SDL2_TEXTURES_H