#include <iostream>
#include "Game.hpp"

#include "include/config.h"

#define kVel 5

int main() {

  //MiModulo *mod = new MiModulo(); //Modulo creado por
  Game game = Game::getInstance();
  game.initGame();
  game.mainLoop();

  
  return 0;
}