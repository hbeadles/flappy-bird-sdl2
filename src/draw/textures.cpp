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

/**
 * @name loadTextTexture
 * @brief Renders text to a texture using the specified font and color.
 * Caches the texture for future use.
 * @param app Application struct reference
 * @param text Text string to render
 * @param color SDL_Color for the text
 * @param font TTF_Font pointer to use for rendering
 * @return SDL_Texture* - Rendered text texture pointer or nullptr on failure
 **/
SDL_Texture* loadTextTexture(Application &app,
    const std::string &text,
    SDL_Color color,
    TTF_Font *font) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (textSurface == nullptr) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return nullptr;
    }
    SDL_Texture* texture = getTexture(app, text);
    if (!texture) {
        texture = SDL_CreateTextureFromSurface(app.renderer, textSurface);
        if (texture == nullptr) {
            printf("Unable to creaet texture from rendered text! SDL Error: %s\n", SDL_GetError());
            return nullptr;
        }
        app.textureCache[text] = texture;
    }

    SDL_FreeSurface(textSurface);
    return texture;
}

