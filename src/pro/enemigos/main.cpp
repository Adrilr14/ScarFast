#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/config.h"
#include "ej_modulos/enemigo.h"

#define kVel 5

int main() {

  Fantasma *fantasma = new Fantasma();
  Minotauro *min = new Minotauro();
  Golem *golem = new Golem();

  //Creamos una ventana
  sf::RenderWindow window(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");


  //Bucle del juego
  while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {

        if(event.type==sf::Event::Closed){
            window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
            window.close();
        }
    }
    window.clear();
    window.draw(fantasma->getSprite());
    window.draw(min->getSprite());
    window.draw(golem->getSprite());
    window.display();
  }

  return 0;
}