#pragma once
#include "arma.hpp"
#include "disparo.hpp"
#include "player.hpp"

class Magia : public Arma{
private:
    int tipo;
    float vel;
    
public:
    Magia(int id, int damage, sf::Sprite *spArma, int tipo, float velocity);
    ~Magia();

    Disparo* disparar(Player *player); 
};