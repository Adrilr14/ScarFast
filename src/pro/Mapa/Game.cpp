#include "Game.hpp"
#include "facade/ControllerMan.hpp"
#include "facade/Controller.hpp"
#include "game/sys/physics.hpp"

Game& Game::getInstance() {
    static Game game;
    return game;
}

void Game::initGame() {
    ControllerMan::instancia().controller().createWindow(widthScreen,heightScreen);
    //Player One Properties
    int hpone = 100;
    Physics_t phynumbone(30,30,0,0);
    Sprite_t s(10,"resources/sprites.png",20,20,false);
    one = new Player(hpone,phynumbone,s);
   
    int hptwo = 100;
    Physics_t phynumbtwo(50,30,0,0);
    Sprite_t x(11,"resources/sprites.png",20,20,false);
    two = new Player(hptwo,phynumbone,x);

    col = new Collision_t;

    mapa = new Map_t();
    mapa->Load_Map();
    ControllerMan::instancia().controller().load_MapSfml(*mapa);
}

void Game::mainLoop() {
    ControllerMan::instancia().controller().setEnviroment();
    while(ControllerMan::instancia().controller().isWindowOpen()){
        one->checkKeyboard();
        one->getCuadrante(*mapa);
        ControllerMan::instancia().controller().run();
    }
}