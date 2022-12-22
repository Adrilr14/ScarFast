#include "enemigo.h"
#include <iostream>  
#include <SFML/Graphics.hpp>


Fantasma::Fantasma(){
  vida=100;
  rango=8;
  if (!this->tex.loadFromFile("resources/Fantasma.png")) {
    std::cerr << "Error cargando la imagen sprites.png";
    exit(0);
  }

  this->sprite.setTexture(this->tex);
  this->sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 720, 480));
  this->sprite.setPosition(40, 240);
  this->sprite.setScale(0.10,0.15);
}

sf::Sprite Fantasma::getSprite(){
  return this->sprite;
}


