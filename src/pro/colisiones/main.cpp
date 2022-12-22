#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/config.h"
//#include "ej_modulos/mimodulo.h"
#include "src/sys/collision.h"

#define kVel 5

int main() {

  //MiModulo *mod = new MiModulo();
  Collision *col = new Collision();

  //Creamos una ventana
  sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(640, 480), "Colisiones");

  //Cargo la imagen donde reside la textura del sprite
  sf::Texture *tex = new sf::Texture;
  if (!(tex->loadFromFile("resources/sprites.png"))) {
    std::cerr << "Error cargando la imagen sprites.png";
    exit(0);
  }

  //Y creo el spritesheet a partir de la imagen anterior
  sf::Sprite *sprite = new sf::Sprite(*tex);

  //Le pongo el centroide donde corresponde
  sprite->setOrigin(75 / 2, 75 / 2);
  //Cojo el sprite que me interesa por defecto del sheet
  sprite->setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));

  // Lo dispongo en el centro de la pantalla
  sprite->setPosition(320, 240);

  //Creamos un segundo sprite
  sf::Sprite *sprite2 = new sf::Sprite(*tex);

  //Le pongo el centroide donde corresponde
  sprite2->setOrigin(75 / 2, 75 / 2);
  //Cojo el sprite que me interesa por defecto del sheet
  sprite2->setTextureRect(sf::IntRect(1 * 75, 0 * 75, 75, 75));

  // Lo dispongo en el centro de la pantalla
  sprite2->setPosition(160, 120);

  //Creamos un vector para guardar la posicion del sprite
  sf::Vector2f oldPosSp (0.f, 0.f);

  //Bucle del juego
  while (window->isOpen()) {
    //Bucle de obtención de eventos
    sf::Event event;
    while (window->pollEvent(event)) {

      switch (event.type) {
      
      //Si se recibe el evento de cerrar la ventana la cierro
      case sf::Event::Closed:
        window->close();
        break;

      //Se pulsó una tecla, imprimo su codigo
      case sf::Event::KeyPressed:

        //Verifico si se pulsa alguna tecla de movimiento
        switch (event.key.code) {

        //Mapeo del cursor
        case sf::Keyboard::Right:
          //Guardamos la posicion actual del sprite
          oldPosSp = sprite->getPosition();

          sprite->move(kVel, 0);
          sprite->setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
          //Escala por defecto
          sprite->setScale(1, 1);

          //Si colisiona se restaura la posicion
          if (col->collidesWith(sprite, sprite2))
          {
            sprite->setPosition(oldPosSp);
          }
          break;

        case sf::Keyboard::Left:
          //Guardamos la posicion actual del sprite
          oldPosSp = sprite->getPosition();
          
          sprite->move(-kVel, 0);
          sprite->setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
          //Reflejo vertical
          sprite->setScale(-1, 1);

          //Si colisiona se restaura la posicion
          if (col->collidesWith(sprite, sprite2))
          {
            sprite->setPosition(oldPosSp);
          }

          break;

        case sf::Keyboard::Up:
          //Guardamos la posicion actual del sprite
          oldPosSp = sprite->getPosition();

          sprite->move(0, -kVel);
          sprite->setTextureRect(sf::IntRect(0 * 75, 3 * 75, 75, 75));

          //Si colisiona se restaura la posicion
          if (col->collidesWith(sprite, sprite2))
          {
            sprite->setPosition(oldPosSp);
          }
          break;

        case sf::Keyboard::Down:
          //Guardamos la posicion actual del sprite
          oldPosSp = sprite->getPosition();

          sprite->move(0, kVel);
          sprite->setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));

          //Si colisiona se restaura la posicion
          if (col->collidesWith(sprite, sprite2))
          {
            sprite->setPosition(oldPosSp);
          }
          break;

        //Tecla ESC para salir
        case sf::Keyboard::Escape:
          window->close();
          break;

        //Cualquier tecla desconocida se imprime por pantalla su código
        default:
          std::cout << event.key.code << std::endl;
          break;
        }
      }
    }

    window->clear();
    window->draw(*sprite);
    //window->draw(*sprite2);
    window->display();
  }

  return 0;
}