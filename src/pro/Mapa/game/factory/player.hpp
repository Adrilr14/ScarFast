#pragma once

#include "character.hpp"
#include "keyboard.hpp" 
#include "../../facade/ControllerMan.hpp"
#include "../../facade/Controller.hpp"
#include <iostream>
#include <vector>

class Player : public Character_t{
private:
    Keyboard_t* keyboard{};
public:
    Player(int hp ,const Physics_t& p,const Sprite_t& t)
    : Character_t(hp,p,t) {
        keyboard = new Keyboard_t();
    };
    ~Player(){};

    void checkKeyboard();
    void getCuadrante(Map_t& mapa);
};