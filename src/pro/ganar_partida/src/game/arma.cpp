#include "arma.hpp"

// Constructor
Arma::Arma(int n, int dmg, sf::Sprite *spArma) : id(n), damage(dmg), sp(spArma) {};

//Destructor
Arma::~Arma() {};

sf::Sprite* Arma::getSprite() {
    return sp;
}

void Arma::setSprite(sf::Sprite* sprite){
    sp = sprite;
}
