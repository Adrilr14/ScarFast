#include "enemigo.h"
#include <iostream>  
#include <SFML/Graphics.hpp>


Golem::Golem(){
  vida=100;
  rango=1;  
  if (!this->tex.loadFromFile("resources/GolemEnemigo.png")) {
    std::cerr << "Error cargando la imagen sprites.png";
    exit(0);
  }

  this->sprite.setTexture(this->tex);
  this->sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 720, 480));
  this->sprite.setPosition(80, 240);
  this->sprite.setScale(0.10,0.15);
}

sf::Sprite Golem::getSprite(){
  return this->sprite;
}


