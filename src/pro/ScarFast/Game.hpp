#pragma once

#include "facade/Controller.hpp"
#include "game/factory/map.hpp"
#include "game/factory/player.hpp"
#include "game/factory/ronda.hpp"
#include "game/factory/animation.hpp"
#include "game/sys/ia.hpp"
#include "game/factory/enemy.hpp"
#include "game/sys/input.hpp"
#include "game/factory/hud.hpp"
#include "game/sys/time.hpp"
#include "State/State.hpp"

class Game_t {

private:
    Game_t() = default;
    static Game_t* game;
    
    //Varibles del game
    Hud* hud;
    Map_t* map;
    Player_t* one;
    Player_t* two;
    Keyboard_t* keyboard;
    State_t* estado;
    Ronda_t* ronda;
    Temporizador_t* temporizador {nullptr};
    Animation_t* animations;
    std::vector<Enemy*> enemies;

    bool gameStarting {false};
    float tiempoJuego {0.f};

    // Functions
    void crearEnemigosShooter();
    void crearEnemigosPatrol();
    void crearEnemigosPursuit();
    void crearEnemigos();

public:
    ~Game_t();
    static Game_t* getInstance();
    void InitGame();
    void MainLoop();
    void setState(State_t::State_type);
    Controller_t* renderEngine {nullptr};

    //Getters y setters
    Map_t* getMap();
    Player_t* getPlayerOne();
    Player_t* getPlayerTwo();
    Keyboard_t* getKeyboard();
    Ronda_t* getRonda();
    Hud* getHud();
    State_t* getState();
    Temporizador_t* getTemporizador();
    Animation_t* getAnimation();
    std::vector<Enemy*> getEnemies();
    bool getGameStart();

    void setTemporizador(Temporizador_t* t);
    void setGameStart(bool b);
};