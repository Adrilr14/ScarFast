#include "Game.hpp"
#include "facade/ControllerMan.hpp"
#include "facade/SfmlGraphics.hpp"

Game& Game::getInstance() {
    static Game game;
    return game;
}

void Game::initGame() {
    ControllerMan::instancia().controller().createWindow();
}

void Game::mainLoop() {
    ControllerMan::instancia().controller().run();
}