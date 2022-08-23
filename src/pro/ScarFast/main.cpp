#include <iostream>
#include "Game.hpp"

int main() {
  Game_t::getInstance()->InitGame();
  Game_t::getInstance()->MainLoop();
}