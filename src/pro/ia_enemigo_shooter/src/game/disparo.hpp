#pragma once

#include <SFML/Graphics.hpp>
#include "direction.hpp"

class Player;

class Disparo{
private:
    int id;
    sf::Sprite *spDisparo;
    int damage;
    int tipo;
    float vel;
    Player *player; // Jugador que dispara
    Direction_t direccion; // Direccion del disparo

public:
    Disparo(int id, sf::Sprite *spDisparo, int damage, int tipo, float velocity, Player *player, Direction_t direccion);
    ~Disparo();

    void mover();

    sf::Sprite* getSprite();
    void setSprite(sf::Sprite *sprite);

    int getDamage();
    void setDamage(int damage);

    Player* getPlayer();
    void setPlayer(Player *player);
};
