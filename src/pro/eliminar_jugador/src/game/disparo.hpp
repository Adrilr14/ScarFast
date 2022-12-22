#pragma once
#include <SFML/Graphics.hpp>
#include "player.hpp"

class Disparo{
private:
    int id;
    sf::Sprite *spDisparo;
    int damage;
    int tipo;
    float vel;
    Player *player; // Jugador que dispara

public:
    Disparo(int id, sf::Sprite *spDisparo, int damage, int tipo, float velocity, Player *player);
    ~Disparo();

    void mover();

    sf::Sprite* getSprite();
    void setSprite(sf::Sprite *sprite);

    int getDamage();
    void setDamage(int damage);
};
