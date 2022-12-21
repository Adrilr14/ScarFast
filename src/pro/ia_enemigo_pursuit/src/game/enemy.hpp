#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class IA;
class Player;

class Enemy{

private:
    int id;
    int hp;
    int damage;
    float velocity;
    sf::Sprite *spEnemy;
    IA *comportamiento;
    sf::Vector2f posIni;
public:
    Enemy(int id, int hp, int damage, float velocity, sf::Sprite *spEnemy, IA *comportamiento, sf::Vector2f posIni);
    ~Enemy();

    void moveEnemy(Player *p);

    //Setters y getters

    int getHP();
    void setHP(int hp);

    int getDamage();
    void setDamage(int damage);

    float getVelocity();
    void setVelocity(float velocity);

    sf::Sprite* getSprite();
    void setSprite(sf::Sprite *spEnemy);

    IA* getComportamiento();
    void setComportamiento(IA *ia);
};