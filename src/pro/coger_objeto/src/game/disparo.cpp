#include "disparo.hpp"

#define kVel 0.03

Disparo::Disparo(int id, sf::Sprite *spDisparo, int damage, float vel, int tipo) : id(id), spDisparo(spDisparo), damage(damage), vel(vel), tipo(tipo) {}

Disparo::~Disparo() {}

void Disparo::mover(){
    spDisparo->move(0, kVel);
}

sf::Sprite* Disparo::getSprite(){
    return spDisparo;
}
