//
// Created by Hayden Beadles on 10/5/25.
//
#include <draw/textures.h>

SDL_Texture* loadTexture(Application & app, const std::string & filename){
    SDL_Texture* texture = getTexture(app, filename);
    if(!texture){
        texture = IMG_LoadTexture(app.renderer, filename.c_str());
        app.textureCache[filename] = texture;
    }
    return texture;
}

SDL_Texture* getTexture(Application & app, const std::string & filename){
    auto it = app.textureCache.find(filename);
    if (it == app.textureCache.end()) {
        // Key not found
        return nullptr;
    }
    // Key found, return the associated texture
    return it->second;
}