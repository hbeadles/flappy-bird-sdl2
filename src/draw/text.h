//
// Created by Hayden Beadles on 10/10/25.
//

#ifndef FLAPPY_BIRD_SDL2_TEXT_H
#define FLAPPY_BIRD_SDL2_TEXT_H
#include <system/common.h>

class Game;

class Text {
public:
    Text(Game* game);
    ~Text() = default;
    void initText();
    void drawNumber(int number, int x, int y);
    void drawScore(int score, int x, int y);
private:
    Game* game;
    AtlasImage* numberTextures[10]{};
};
#endif //FLAPPY_BIRD_SDL2_TEXT_H