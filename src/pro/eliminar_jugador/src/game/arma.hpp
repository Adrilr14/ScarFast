#pragma once
#include <SFML/Graphics.hpp>

class Arma{
protected:
    int id;
    int damage;
    sf::Sprite *sp;

public:
    Arma(int n, int dmg, sf::Sprite *spArma);
    ~Arma();

    virtual sf::Sprite* getSprite();
    virtual void setSprite(sf::Sprite *sprite);

    virtual int getDamage();
    virtual void setDamage(int damage);
};
