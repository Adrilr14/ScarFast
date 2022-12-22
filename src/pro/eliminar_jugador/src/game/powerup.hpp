#pragma once
#include <SFML/Graphics.hpp> 

class Powerup{
private:
    int id;
    sf::Sprite *spPowerup;
    int tipo;
    int duracion;

public:
    Powerup(int n, sf::Sprite *sprite, int tipo, int duracion);
    ~Powerup();

    sf::Sprite* getSprite();
    void setSprite(sf::Sprite *sprite);

    int getTipo();
    void setTipo(int tipo);

    int getDuracion();
    void setDuracion(int duracion);
};
