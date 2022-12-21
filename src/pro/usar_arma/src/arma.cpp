#include "arma.hpp"

Arma::Arma(int id, int damage, sf::Sprite *spArma) : id(id), damage(damage), spArma(spArma){}

sf::Sprite* Arma::getSprite() {
    return spArma;
}