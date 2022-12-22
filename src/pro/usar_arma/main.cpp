#include <SFML/Graphics.hpp>
#include <iostream>
#include "src/magia.hpp"
#include "include/config.h"
#include "src/player.hpp"
#include "src/disparo.hpp"
#include "src/espada.hpp"

#define kVel 5

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
   return dynamic_cast<const Base*>(ptr) != nullptr;
}

sf::Sprite* createSprite(std::string nameSprite, sf::Vector2f pos, int width, int height, int col, int fila){
  //Cargo la imagen donde reside la textura del sprite
  sf::Texture *tex = new sf::Texture;
  if (!(tex->loadFromFile("resources/"+nameSprite))) {
    std::cerr << "Error cargando la imagen sprites.png";
    exit(0);
  }

  //Y creo el spritesheet a partir de la imagen anterior
  sf::Sprite *spriteNew = new sf::Sprite(*tex);

  //Le pongo el centroide donde corresponde
  spriteNew->setOrigin(width / 2, height / 2);
  //Cojo el sprite que me interesa por defecto del sheet
  spriteNew->setTextureRect(sf::IntRect(fila * width, col * height, width, height));

  // Lo dispongo en el centro de la pantalla
  spriteNew->setPosition(pos);
  
  return spriteNew;
}
int main() {

  Disparo *disparoBola = nullptr; 
  //Creamos una ventana
  sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(640, 480), "Armas");

  //Creamos sprite
  sf::Vector2f pos (320.f, 240.f);
  sf::Sprite* sprite = createSprite("sprites.png", pos, 75, 75, 0, 0);
  //Creamos una espada
  sf::Sprite* spAtacar = createSprite("sprites.png", pos, 75, 75, 1, 1);
  int idEspada = 1;
  int damageEsp = 1;
  Espada *espada = new Espada(idEspada, damageEsp, spAtacar);
  //Creamos magia
  int damageMagia = 1;
  int idMagia = 1;
  sf::Sprite* spMagia = createSprite("bola.png", sf::Vector2f (0.f, 0.f), 64, 64, 0, 0);
  Magia *magia = new Magia(idMagia, damageMagia, spMagia);
  //Creamos player
  Player *jugador1 = new Player(sprite, espada);

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
          jugador1->getSprite()->move(kVel, 0);
          jugador1->getSprite()->setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
          //Escala por defecto
          jugador1->getSprite()->setScale(1, 1);
            //direccion de arma
            magia->direccion.dir = 1;
         
          break;

        case sf::Keyboard::Left:
          jugador1->getSprite()->move(-kVel, 0);
          jugador1->getSprite()->setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
          //Reflejo vertical
          jugador1->getSprite()->setScale(-1, 1);

            //direccion de arma
            magia->direccion.dir = 2;
          break;

        case sf::Keyboard::Up:
          jugador1->getSprite()->move(0, -kVel);
          jugador1->getSprite()->setTextureRect(sf::IntRect(0 * 75, 3 * 75, 75, 75));
            //direccion de arma
            magia->direccion.dir = 4;
          break;

        case sf::Keyboard::Down:
          jugador1->getSprite()->move(0, kVel);
          jugador1->getSprite()->setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));
            //direccion de arma
            magia->direccion.dir = 3;
          break;

        case sf::Keyboard::Enter:
          
          if(instanceof<Magia>(jugador1->getArma())){
            disparoBola = static_cast<Magia*>(jugador1->getArma())->disparar(jugador1->getSprite()->getPosition(), magia->direccion);
          }
           else if(instanceof<Espada>(jugador1->getArma())){
            jugador1->getSprite()->setTextureRect(sf::IntRect(1 * 75, 1 * 75, 75, 75));
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
    window->draw(*jugador1->getSprite());
    if(disparoBola != nullptr){
      window->draw(*(disparoBola->getSprite()));
      disparoBola->mover(disparoBola->getSprite());
    }
    window->display();
  }

  return 0;
}

