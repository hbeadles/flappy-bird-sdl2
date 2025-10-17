//
// Created by Hayden Beadles on 10/10/25.
//

#ifndef FLAPPY_BIRD_SDL2_TEXT_H
#define FLAPPY_BIRD_SDL2_TEXT_H
#include <system/common.h>

class Game;
/**
 *@class Text
 *@brief Text Rendering class that uses textures to display / render numbers to a screen
 *@name Text
 *@author Hayden Beadles
 */
class Text {
public:
    Text(Game* game);
    ~Text();
    void initText();
    void loadFonts();

    void drawNumber(int number, int x, int y);
    void drawScore(int score, int x, int y);
    TTF_Font * getFont() {return font;}
private:
    TTF_Font *font;
    Game* game;
    SDL_Rect* numberText;
    // AtlasImage* numberTextures[10]{};
    SDL_Texture* numberTexturesTexture[10]{};
};
#endif //FLAPPY_BIRD_SDL2_TEXT_H