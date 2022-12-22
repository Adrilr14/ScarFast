#pragma once

#include <SFML/Graphics.hpp>

class Player;
class Disparo;

// Enumeración para saber que tipo de arma es
enum TipoArma {espada = 0, magia = 1};

class Arma{

private:
    int id;
    int damage;
    sf::Sprite *sp;
    int tipoMagia;
    float velocity;
    int tipoArma;

public:
    Arma(int id, int damage, sf::Sprite *spArma); // Constructor de Espada
    Arma(int id, int damage, sf::Sprite *spArma, int tipo, float vel); // Constructor de Magia
    ~Arma();

    Disparo* disparar(Player *player);

    sf::Sprite* getSprite();
    void setSprite(sf::Sprite *sprite);

    int getDamage();
    void setDamage(int damage);

    int getTipoMagia();
    void setTipoMagia(int tipoMagia);

    float getVelocity();
    void setVelocity(float velocity);

    int getTipoArma();
    void setTipoArma(int tipoArma);
};
