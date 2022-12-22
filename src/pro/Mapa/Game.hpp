#pragma once

#include "game/factory/player.hpp"
#include "game/factory/map.hpp"
#include "game/sys/collision.hpp"



class ControllerMan;

class Game{
    
private:
    Game() = default;
    bool gameStart {false};
    bool fullScreen {false};
    int widthScreen {940};
    int heightScreen {540};
    Player* one;
    Player* two;
    Map_t* mapa;
    Collision_t* col;
public:
    virtual ~Game(){};
    static Game& getInstance();
    void initGame();
    void mainLoop();
};
