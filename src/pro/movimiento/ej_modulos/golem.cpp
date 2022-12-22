#include "golem.h"
#include <SFML/Graphics.hpp>

#include <iostream>

#define kVel 3.5


golem::golem() {
   std::cout << "Creando mi golem..."; 


  //Cargo la imagen donde reside la textura del sprite
  if (!this->tex.loadFromFile("resources/golem1.png")) {
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
  this->sprite.setPosition(40, 240);

  this->sprite.setScale(0.10,0.15);


}

sf::Sprite golem::getSprite(){
return this->sprite;
}

void golem::update(){
    this->movimiento();
}

void golem::movimiento(){


      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            this->sprite.move(-kVel, -kVel);
      }else{
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
                  this->sprite.move(-kVel, 0);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
                  this->sprite.move(kVel, 0);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
                  this->sprite.move(0, -kVel);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
                  this->sprite.move(0, kVel);
            } 
      }

      
}