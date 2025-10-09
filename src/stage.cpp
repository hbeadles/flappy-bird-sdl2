//
// Created by Hayden Beadles on 10/5/25.
//

#include <stage.h>
#include <game.h>

Stage::Stage(Game *game, StageType type) : game(game), type(type) {
}

void Stage::init() {
    // Default implementation - can be overridden by derived classes
}
bool Stage::hasPipeManager() {
    return game->pipe_manager != nullptr;
}

void Stage::handleInput(const Uint8* state) {
    // Default implementation - can be overridden by derived classes
}

StageType Stage::update(float deltaTime) {
    // Default implementation - can be overridden by derived classes
    return StageType::NONE;
}

void Stage::reset() {
    // Default implementation - can be overridden by derived classes
}

void Stage::draw() {
    // Default implementation - can be overridden by derived classes
}

StageType Stage::getType() const {
    return type;
}
