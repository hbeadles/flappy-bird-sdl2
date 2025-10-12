//
// Created by Hayden Beadles on 10/5/25.
//
#include <draw/textures.h>

/**
 * @name loadTexture
 * @brief Loads a texture from file if not already loaded and caches it.
 * If the texture is already loaded, returns the cached texture.
 * @param app Application struct reference
 * @param filename Filename of the texture to load
 * @return SDL)_Texture* - Loaded texture pointer
 */
SDL_Texture* loadTexture(Application & app, const std::string & filename){
    SDL_Texture* texture = getTexture(app, filename);
    if(!texture){
        texture = IMG_LoadTexture(app.renderer, filename.c_str());
        app.textureCache[filename] = texture;
    }
    return texture;
}

/**
 * @name getTexture
 * @brief Retrieves a cached texture by filename.
 * Returns nullptr if the texture is not found in the cache.
 * @param app Application struct reference
 * @param filename Filename of the texture to retrieve
 * @return SDL_Texture* - Retrieved texture pointer or nullptr if not found
 */
SDL_Texture* getTexture(Application & app, const std::string & filename){
    auto it = app.textureCache.find(filename);
    if (it == app.textureCache.end()) {
        // Key not found
        return nullptr;
    }
    // Key found, return the associated texture
    return it->second;
}