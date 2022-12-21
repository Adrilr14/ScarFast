#include "disparo.hpp"

Disparo::Disparo(int id, sf::Sprite *spDisparo, int damage, int tipo, float v, Player *p) : id(id), spDisparo(spDisparo), damage(damage), tipo(tipo), vel(v), player(p) {}

Disparo::~Disparo() {}

void Disparo::mover() {
    spDisparo->move(0, vel);
}

sf::Sprite* Disparo::getSprite() {
    return spDisparo;
}

int Disparo::getDamage() {
    return damage;
}

void Disparo::setDamage(int d) {
    damage = d;
}
