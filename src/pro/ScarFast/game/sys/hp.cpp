#include "hp.hpp"

// Constructor
Hp_t::Hp_t(int h, int s) : hp(h), shield(s), max_hp(h) {};

// Destructor
Hp_t::~Hp_t() {}

bool Hp_t::is_alive() {
    if(hp > 0) 
    {
        return true;
    }
    return false;
}

void Hp_t::reduceHp(int damage) {
    if (invulnerabilidad){
        return;
    }
    
    if(shield > 0){
        if (shield >= damage){
            shield -= damage;
        }else{
            shield = 0;
            damage -= shield;
            if (hp >= damage){
                hp -= damage;
            }else{
                hp = 0;
            }
        }
    }
    else{
        if (hp >= damage){
            hp -= damage;
        }
        else
        {
            hp = 0;
        }
    }
}

int Hp_t::getHp() {
    return hp;
}

void Hp_t::setHp(int vida) {
    hp = vida;
}

int Hp_t::getShield() {
    return shield;
}

void Hp_t::setShield(int escudo) {
    shield = escudo;
}

void Hp_t::revivir(){
    hp = max_hp;
}

void Hp_t::setVulnerabilidad(bool s) {
    invulnerabilidad = s;
}