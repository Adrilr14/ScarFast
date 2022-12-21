#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class IA;
class Player;
class Disparo;

class Enemy{

private:
    int id;
    int hp;
    int damage;
    float velocity;
    sf::Sprite *spEnemy;
    IA *comportamiento;
    int patrolPosition {0};
    int tipoMagia;
    bool puedeDisparar;
    float cadenciaDisparo;

public:
    Enemy(int id, int hp, int damage, float velocity, sf::Sprite *spEnemy, IA *comportamiento);
    Enemy(int id, int hp, int damage, float velocity, sf::Sprite *spEnemy, IA *comportamiento, int tipoMagia, float cadenciaDisparo); // Enemy shooter
    ~Enemy();

    void moveEnemy(Player *pl);
    Disparo* dispararEnemy(Player *pl);

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

    int getTipoMagia();
    void setTipoMagia(int tipoMagia);

    bool getPuedeDisparar();
    void setPuedeDisparar(bool puedeDisparar);

    float getCadenciaDisparo();
    void setCadenciaDisparo(float cadenciaDisparo);
};