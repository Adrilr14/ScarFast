#pragma once
#include "arma.hpp"
#include "disparo.hpp"
#include "player.hpp"

class Magia : public Arma{
private:
    
public:
    Magia(int id, int damage, sf::Sprite *spArma);
    ~Magia();

    Disparo* disparar(sf::Vector2f posPlayer); 
};