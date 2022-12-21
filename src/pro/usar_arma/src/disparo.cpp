#include "disparo.hpp"

#define kVel 0.03

Disparo::Disparo(int id, sf::Sprite *spDisparo, int damage, float vel, int tipo, Direction_t d) : id(id), spDisparo(spDisparo), damage(damage), vel(vel), tipo(tipo), direccion(d){}

Disparo::~Disparo() {}

void Disparo::mover(sf::Sprite *spBola){
    spBola->move(direccion.valuesDirection[direccion.dir].m_x * kVel, direccion.valuesDirection[direccion.dir].m_z*kVel);
}

sf::Sprite* Disparo::getSprite(){
    return spDisparo;
}