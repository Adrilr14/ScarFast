#pragma once
#include <SFML/Graphics.hpp>
#include "direction.hpp"

class Arma{
protected:
    int id;
    int damage;
    sf::Sprite *spArma;

public:
    Arma(int id, int damage, sf::Sprite *spArma);
    ~Arma() {};
    Direction_t direccion;
    virtual sf::Sprite* getSprite();

};