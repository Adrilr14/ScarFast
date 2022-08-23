#pragma once

#include "../sys/direction.hpp"
#include "sprite.hpp"

enum Objetivo {
    player_one = 1,
    player_two = 2,
    both = 3
};

class Disparo{
private:
    EntityID_t entityID { ++nextID };
	inline static EntityID_t nextID {0};
    Sprite_t *spDisparo;
    int damage;
    int tipo;
    float vel {5};
    Objetivo objet {Objetivo::both};
    Direction_t direccion; // Direccion del disparo

public:
    Disparo(Sprite_t *spDisparo, int damage, int tipo, float velocity, Direction_t direccion, Objetivo o);
    ~Disparo();

    void mover();

    Sprite_t* getSprite();
    void setSprite(Sprite_t  *sprite);

    int getDamage();
    void setDamage(int damage);

    EntityID_t getID() {
        return entityID;
    }

    EntityID_t getEntity() {
        return entityID;
    }

    Objetivo getObjetivo(){
        return objet;
    }
};

struct Map_Disparos {
    inline static std::map<EntityID_t,Disparo*> disparos;
};