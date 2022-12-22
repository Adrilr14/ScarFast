#pragma once

#include "sprite.hpp"
#include "../sys/physics.hpp"

class Character_t {
    /** Clase para definir
     *  tanto enemigos como jugadores **/    
protected:
    int hp;
    Physics_t phy;
    Sprite_t sp;
    State estado {State::alive};
public:
    Character_t(const Physics_t& p, const Sprite_t& t) : phy(p), sp(t) {};
    virtual ~Character_t() = default;
};