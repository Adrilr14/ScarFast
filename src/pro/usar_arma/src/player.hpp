#pragma once

#include <SFML/Graphics.hpp>
#include "arma.hpp"

class Player{
public:
    Player(sf::Sprite *sprite, Arma *a);
    ~Player();
    sf::Sprite* getSprite();
    void setSprite(sf::Sprite *sprite);
    Arma* getArma();
    void setArma(Arma *a);

private:
    //atributos
    sf::Sprite *sp;
    Arma *a;
};