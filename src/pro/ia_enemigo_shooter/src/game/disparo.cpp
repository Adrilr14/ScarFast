#include "disparo.hpp"
#include "player.hpp"

Disparo::Disparo(int id, sf::Sprite *spDisparo, int damage, int tipo, float v, Player *p, Direction_t d) : id(id), spDisparo(spDisparo), damage(damage), tipo(tipo), vel(v), player(p), direccion(d) {}

Disparo::~Disparo() {}

void Disparo::mover() {
    spDisparo->move(direccion.valuesDirection[direccion.dir].m_x * vel, direccion.valuesDirection[direccion.dir].m_z * vel);
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

Player* Disparo::getPlayer() {
    return player;
}

void Disparo::setPlayer(Player *pl) {
    player = pl;
}
