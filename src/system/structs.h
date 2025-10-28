//
// Created by Hayden Beadles on 10/5/25.
//

#ifndef FLAPPY_BIRD_SDL2_STRUCTS_H
#define FLAPPY_BIRD_SDL2_STRUCTS_H
#include <SDL2/SDL.h>
#include <unordered_map>
#include <imgui/imgui.h>

typedef struct AtlasImage AtlasImage;
typedef struct Pipe Pipe;
typedef struct Flappy Flappy;
typedef struct Application Application;
typedef struct Animation Animation;
typedef struct Vec2 Vec2;

struct Vec2 {
    double x, y;
    Vec2() : x(0), y(0) {}
    Vec2(double x_, double y_) : x(x_), y(y_) {}

    Vec2 operator+(const Vec2& o) const { return Vec2(x + o.x, y + o.y); }
    Vec2 operator-(const Vec2& o) const { return Vec2(x - o.x, y - o.y); }
    Vec2 operator*(double s)    const { return Vec2(x * s, y * s); }
    Vec2 operator/(double s)    const { return Vec2(x / s, y / s); }

    Vec2& operator+=(const Vec2& o) { x += o.x; y += o.y; return *this; }
    Vec2& operator-=(const Vec2& o) { x -= o.x; y -= o.y; return *this; }
    Vec2& operator*=(double s)      { x *= s; y *= s; return *this; }
    Vec2& operator/=(double s)      { x /= s; y /= s; return *this; }

    double dot(const Vec2& o) const { return x * o.x + y * o.y; }
    double length() const { return std::sqrt(x * x + y * y); }
    Vec2 normalized() const { double len = length(); return len ? (*this) / len : Vec2(0, 0); }
    Vec2 rotated(double angle) const {
        double cosA = std::cos(angle), sinA = std::sin(angle);
        return {x * cosA - y * sinA, x * sinA + y * cosA};
    }
    Vec2 perp(double scale = 1.0) const {
        // 90-degree CCW, scaled
        return Vec2(-y * scale, x * scale);
    }
    static Vec2 fromAngle(double angle) {
        return Vec2(std::cos(angle), std::sin(angle));
    }
};

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
    float midX{};
    float midY{};
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
    SDL_Texture* renderTarget;
    int screenWidth;
    int screenHeight;
    ImGuiIO* io;
    ImGuiStyle* style;
    double deltaTime;
    std::unordered_map<std::string, AtlasImage*> atlas;
    std::unordered_map<std::string, SDL_Texture*> textureCache;
};
#endif //FLAPPY_BIRD_SDL2_STRUCTS_H