#include "game/game.hpp"

namespace Zero {

Game::Game(std::string title, int flags) : WindowManager(title, flags) {
    gameLogger->debug("Created Game object");
    
    run();
}

Game::~Game() {
    gameLogger->debug("Deleted Game object");
}

void Game::updateEvents() {

    
}

void Game::update() {

}

void Game::render() {

}

void Game::run() {
    gameLogger->debug("Running game loop");
    mainLoop();

}

}
