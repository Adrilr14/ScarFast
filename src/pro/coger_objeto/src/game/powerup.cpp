#include "powerup.hpp"

//Constructor
Powerup::Powerup(int n, sf::Sprite *sprite, int t, int d) : id(n), spPowerup(sprite), tipo(t), duracion(d) {}

//Destructor
Powerup::~Powerup() {}

sf::Sprite* Powerup::getSprite() {
    return spPowerup;
}

void Powerup::setSprite(sf::Sprite *sprite) {
    spPowerup = sprite;
}

int Powerup::getTipo() {
    return tipo;
}

void Powerup::setTipo(int t) {
    tipo = t;
}

int Powerup::getDuracion() {
    return duracion;
}

void Powerup::setDuracion(int d) {
    duracion = d;
}
