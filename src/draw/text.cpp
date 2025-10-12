//
// Created by Hayden Beadles on 10/10/25.
//
#include <draw/text.h>
#include <game/game.h>
#include <system/atlas.h>
#include <draw/draw.h>

/**
 * @name Text
 * @brief Constructor for Text class, used in @flappy_bird_stage.cpp
 * @param game - Game object, dependency injection
 * @memberof Text
 */
Text::Text(Game* game): game(game) {
    initText();
}

/**
 * @name initText
 * @brief Initializes the number textures used for rendering numbers on screen.
 * Loads textures for digits 0-9 from the atlas and stores them in the numberTextures array.
 * Called in the constructor.
 * @memberof Text
 */
void Text::initText() {
    for (int i = 0; i < 10; i++) {
        std::string filename = "gfx/number-" + std::to_string(i) + ".png";
        numberTextures[i] = getAtlasImage(game->app, filename);
    }
}

/**
 * @name drawNumber
 * @brief Draws a single digit number (0-9) at the specified (x, y) coordinates on the screen.
 * Uses the preloaded number textures.
 * @param number - Integer digit to draw (0-9)
 * @param x - X coordinate on screen
 * @param y - Y coordinate on screen
 * @memberof Text
 */
void Text::drawNumber(int number, int x, int y) {
    if (number >= 0 && number <= 9) {
        blitAtlasImage(game->app, numberTextures[number], x, y, 0, SDL_FLIP_NONE);
    }
}

/**
 * @name drawScore
 * @brief Draws a multi-digit score at the specified (x, y) coordinates on the screen.
 * Breaks the score into individual digits and draws each digit using drawNumber.
 * @param score - Integer score to draw (can be multiple digits)
 * @param x - X coordinate on screen
 * @param y - Y coordinate on screen
 * @memberof Text
 */
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