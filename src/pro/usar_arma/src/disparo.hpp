#pragma once
#include <SFML/Graphics.hpp> 
#include "direction.hpp"

class Disparo{
private:
    int id;
    sf::Sprite *spDisparo;
    int damage;
    float vel;
    int tipo;
    Direction_t direccion;
public:
    Disparo(int id, sf::Sprite *spDisparo, int damage, float vel, int tipo, Direction_t d);
    ~Disparo();

    void mover(sf::Sprite *spDisparo);

    sf::Sprite* getSprite();
};