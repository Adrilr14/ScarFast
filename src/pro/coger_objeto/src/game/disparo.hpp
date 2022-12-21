#pragma once
#include <SFML/Graphics.hpp> 

class Disparo{
private:
    int id;
    sf::Sprite *spDisparo;
    int damage;
    float vel;
    int tipo;

public:
    Disparo(int id, sf::Sprite *spDisparo, int damage, float vel, int tipo);
    ~Disparo();

    void mover();

    sf::Sprite* getSprite();
};
