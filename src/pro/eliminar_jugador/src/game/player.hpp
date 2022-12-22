#pragma once

#include <SFML/Graphics.hpp>
#include "arma.hpp"
#include "powerup.hpp"

class Player{
public:
    Player(sf::Sprite *sprite, int hp, Arma *a);
    ~Player();

    void soltarKit();

    sf::Sprite* getSprite();
    void setSprite(sf::Sprite *sprite);

    int getHP();
    void setHP(int hp);

    Arma* getArma();
    void setArma(Arma *a);

    Powerup* getPowerup();
    void setPowerup(Powerup *pow);

    sf::Sprite* getKit();
    void setKit(sf::Sprite *sprite);

private:
    //atributos
    sf::Sprite *sp;
    int hp;
    Arma *a;
    Powerup *power_up;
    sf::Sprite *kit;
};
