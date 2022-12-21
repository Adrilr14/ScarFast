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
    int patrolPosition {0};

public:
    Enemy(int id, int hp, int damage, float velocity, sf::Sprite *spEnemy, IA *comportamiento);
    ~Enemy();

    void moveEnemy(Player *pl);

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