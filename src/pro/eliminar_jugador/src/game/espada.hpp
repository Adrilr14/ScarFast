#pragma once

#include "arma.hpp"

class Espada : public Arma{
private:
    
public:
    Espada(int id, int damage, sf::Sprite *spArma);
    ~Espada();
};