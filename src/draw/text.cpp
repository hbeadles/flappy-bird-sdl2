//
// Created by Hayden Beadles on 10/10/25.
//
#include <draw/text.h>
#include <game/game.h>
#include <system/atlas.h>
#include <draw/draw.h>

Text::Text(Game* game): game(game) {
    initText();
}

void Text::initText() {
    for (int i = 0; i < 10; i++) {
        std::string filename = "gfx/number-" + std::to_string(i) + ".png";
        numberTextures[i] = getAtlasImage(game->app, filename);
    }
}

void Text::drawNumber(int number, int x, int y) {
    if (number >= 0 && number <= 9) {
        blitAtlasImage(game->app, numberTextures[number], x, y, 0, SDL_FLIP_NONE);
    }
}

void Text::drawScore(int score, int x, int y) {
    if (score == 0) {
        drawNumber(0, x, y);
        return;
    }

    // Convert score to string to get digits
    std::string scoreStr = std::to_string(score);
    int digitWidth = numberTextures[0]->rect.w; // Assuming all digits have same width

    // Draw each digit from left to right
    for (size_t i = 0; i < scoreStr.length(); i++) {
        int digit = scoreStr[i] - '0'; // Convert char to int
        drawNumber(digit, x + (i * digitWidth), y);
    }
}