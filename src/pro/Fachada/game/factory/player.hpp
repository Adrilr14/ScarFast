#pragma once

#include "character.hpp"

class Player : public Character_t{
private:
    
public:
    Player(const Physics_t& p,const Sprite_t& t): Character_t(p,t) {};
    ~Player();
};