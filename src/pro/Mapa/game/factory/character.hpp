#pragma once

#include "sprite.hpp"
#include "util.hpp"
#include "../sys/physics.hpp"
#include "../sys/direction.hpp"

#define TILES_WIDTH     20
#define TILES_HEIGHT    20


class Character_t {
    /** Clase para definir
     *  tanto enemigos como jugadores **/    
protected:
    Entity_ID entity_id { ++nextID };
    inline static Entity_ID nextID {0};
    int hp {100};
    Physics_t phy;
    Sprite_t sp;
    Direction_t* direc;
    State estado {State::alive};
public:
    Character_t(int life, const Physics_t& p, const Sprite_t& t) 
    : hp(life) ,phy(p), sp(t) {
        direc = new Direction_t();
    };
    virtual ~Character_t() = default;
};