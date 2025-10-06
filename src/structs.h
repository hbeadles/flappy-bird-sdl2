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

struct Flappy{
    float x;
    float y;
    float dx;
    float dy;
    AtlasImage * texture;
    int health;
    bool active = true;
    float animTimer;
    int currentFrame;
    bool isJumping;
    bool jumpKeyPressedLastFrame;
    float rotation;  // Current rotation angle in degrees
};

struct AtlasImage
{
    SDL_Rect rect;
    SDL_Texture* texture;
    int rotated;
};
struct Pipe {
    float x;
    float y;
    bool isTop;
    AtlasImage * texture;
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

};
#endif //FLAPPY_BIRD_SDL2_STRUCTS_H