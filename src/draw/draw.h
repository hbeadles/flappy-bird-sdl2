#ifndef FLAPPY_BIRD_SDL2_DRAW_H
#define FLAPPY_BIRD_SDL2_DRAW_H
#include <system/common.h>

void prepareScene(Application & app);
void prepareSceneWithCamera(Application & app);
void presentSceneWithCamera(Application & app, float rotation, SDL_Point* center);
void presentScene(Application & app);
void blit(Application & app, SDL_Texture * texture, int x, int y, double angle =0, SDL_RendererFlip flip = SDL_FLIP_NONE);
void blitAtlasImage(Application & app, AtlasImage * image, int x, int y, int center, double angle =0, SDL_RendererFlip flip = SDL_FLIP_NONE);
void blitEx(Application & app, SDL_Texture* texture,
    SDL_Rect* srcRect, SDL_Rect* destRect, double angle, SDL_Point* center, SDL_RendererFlip flip= SDL_FLIP_NONE);
void colorModulate(SDL_Texture* texture, Uint8 r, Uint8 g, Uint8 b);

double evaluateBezier(double *data, int ndata, double t);
int bezierRGBA(SDL_Renderer* renderer, const Sint16 * vx, const Sint16 * vy, int n, int s, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
int bezierRGBASDL(SDL_Renderer* renderer, std::vector<SDL_Point> points, int s, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void drawVector(Application& app, float startX, float startY, float dirX, float dirY, float length, SDL_Color color);
void drawArrow(Application& app, float startX, float startY, float endX, float endY, SDL_Color color);
#endif