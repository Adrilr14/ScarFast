#include "minotauro.h"
#include <SFML/Graphics.hpp>

#include <iostream>

#define kVel 4


minotauro::minotauro() {
   std::cout << "Creando mi minotauro..."; 


  //Cargo la imagen donde reside la textura del sprite
  if (!this->tex.loadFromFile("resources/minotauro1.png")) {
    std::cerr << "Error cargando la imagen sprites.png";
    exit(0);
  }

  //Y creo el spritesheet a partir de la imagen anterior
  this->sprite.setTexture(this->tex);



  //Le pongo el centroide donde corresponde
  //sprite.setOrigin(75 / 2, 75 / 2);
  //Cojo el sprite que me interesa por defecto del sheet
  this->sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 720, 480));

  // Lo dispongo en el centro de la pantalla
  this->sprite.setPosition(500, 240);

  this->sprite.setScale(0.10,0.15);


}

sf::Sprite minotauro::getSprite(){
return this->sprite;
}

void minotauro::update(){
    this->movimiento();
}

void minotauro::movimiento(){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
          this->sprite.move(-kVel, 0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
          this->sprite.move(kVel, 0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
          this->sprite.move(0, -kVel);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
          this->sprite.move(0, kVel);
    }
      
}