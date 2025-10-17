//
// Created by Hayden Beadles on 10/5/25.
//

#ifndef FLAPPY_BIRD_SDL2_STRUCTS_H
#define FLAPPY_BIRD_SDL2_STRUCTS_H
#include <SDL2/SDL.h>
#include <unordered_map>

typedef struct AtlasImage AtlasImage;
typedef struct Pipe Pipe;
typedef struct Flappy Flappy;
typedef struct Application Application;
typedef struct Animation Animation;



struct Flappy{
    float x;
    float y;
    float dx;
    float dy;
    AtlasImage * idleTexture;
    std::vector<AtlasImage *>  jumpTextures;
    int health = 1.0f;
    bool active = true;
    //Animation * jumpAnimation;
    int currentFrame;
    float frameTime = 1.0f /24.0f;
    float animTimer = 0.0f;
    float jumpAngle;
    bool isJumping;
};

struct AtlasImage
{
    SDL_Rect srcRect;
    int scale;
    SDL_Rect rect;
    SDL_Texture* texture;
    int rotated;
};
struct Pipe {
    float x{};
    float y{};
    AtlasImage * texture;
    bool isTop{};
    bool active = false;
    bool passed = false;
};
/**
 * @name Application
 * @brief Main application structure holding SDL window, renderer, screen dimensions, delta time, etc.
 * Also contains ImGUI IO and style pointers for UI rendering.
 * @struct Application
 */
struct Application {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int screenWidth;
    int screenHeight;
    double deltaTime;
    std::unordered_map<std::string, AtlasImage*> atlas;
    std::unordered_map<std::string, SDL_Texture*> textureCache;


};
#endif //FLAPPY_BIRD_SDL2_STRUCTS_H