#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/config.h"

#include "src/sys/collision.hpp"
#include "src/game/magia.hpp"
#include "src/game/espada.hpp"
#include "src/game/player.hpp"
#include "src/game/disparo.hpp"
#include "src/game/powerup.hpp"
#include "src/game/ronda.hpp"

//#define kVel 5
#define pos_playerx 50
#define pos_playery 240

enum rounds {
    ronda_menor =  1,
    ronda_inter =  3,
    ronda_super =  5
};

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

  //Declaramos la velocidad
  int kVel = 5;

  //Creamos una ronda
  Ronda* r = new Ronda(rounds::ronda_inter);

  Disparo *disparoBola = nullptr;

  std::vector<Arma*> armasMapa; //Array para comprobar las colisiones con las armas del mapa
  std::vector<Powerup*> powerupsMapa; //Array para comprobar las colisiones con los powerups del mapa

  //Creamos un objeto Collsion para detectar colisiones
  Collision *col = new Collision();

  //Creamos una ventana
  sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(640, 480), "Colisiones");
  
  //Creamos magia
  int idMagia = 1;
  int damageMagia = 1;
  sf::Sprite* spMagia = createSprite("bola.png", sf::Vector2f (160.f, 120.f), 64, 64, 0, 0);
  Magia *magia = new Magia(idMagia, damageMagia, spMagia);

  //Creamos espada
  int idEspada = 1;
  int damageEspada = 1;
  sf::Sprite* spEspada = createSprite("sprites.png", sf::Vector2f(0.f, 0.f), 75, 75, 1, 1);
  Espada *espada = new Espada(idEspada, damageEspada, spEspada);

  //Creamos player
  sf::Sprite* sprite = createSprite("sprites.png", sf::Vector2f(pos_playerx, pos_playery), 75, 75, 0, 0);
  Player *jugador1 = new Player(sprite, espada);

  //Creamos powerup
  sf::Sprite* spPowerup = createSprite("crate_powerup.png", sf::Vector2f(480.f, 360.f), 20, 30, 0, 0);
  Powerup *pow1 = new Powerup(1, spPowerup, 0, 5);

  //Creamos el kit
  sf::Sprite* kit = createSprite("healkit.png", sf::Vector2f(320.f, 240.f), 40, 43, 0, 0);

  //Creamos el respawn
  sf::Sprite* respawn_player_one = createSprite("spawn_red.png", sf::Vector2f(34.f, 240.f), 34, 34, 0, 0);

  sf::Sprite* respawn_player_two = createSprite("spawn_blue.png", sf::Vector2f(604.f, 240.f), 34, 34, 0, 0);


  bool kitCogido = false;

  //Metemos la magia en el array de armas del mapa
  armasMapa.push_back(magia);

  //Metemos el power-up en el array de powerups
  powerupsMapa.push_back(pow1);

  //Creamos un vector para guardar la posicion del sprite
  sf::Vector2f oldPosSp (0.f, 0.f);

  //Bucle del juego
  while (window->isOpen()) {
    //Bucle de obtención de eventos

    if (col->collidesWith(jugador1->getSprite(), respawn_player_two) && kitCogido){
        r->sumarRonda();
        if(r->ganarPartida()){
            std::cout << "Ha ganado la partida" << std::endl;
        }else{
          jugador1->getSprite()->setPosition(pos_playerx,pos_playery);
          kitCogido = false;
        }
    }
    std::cout << std::endl;
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
          oldPosSp = jugador1->getSprite()->getPosition();

          jugador1->getSprite()->move(kVel, 0);
          jugador1->getSprite()->setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
          //Escala por defecto
          jugador1->getSprite()->setScale(1, 1);

          //Si colisiona con alguna arma se coge
          for (unsigned int i = 0; i < armasMapa.size(); i++)
          {
            if (col->collidesWith(jugador1->getSprite(), armasMapa[i]->getSprite()))
            {
              jugador1->setArma(armasMapa[i]);
              armasMapa.erase(armasMapa.begin()+i);
            }
          }

          //Si colisiona con algun power-up se coge
          for (unsigned int i = 0; i < powerupsMapa.size(); i++)
          {
            if (col->collidesWith(jugador1->getSprite(), powerupsMapa[i]->getSprite()))
            {
              jugador1->setPowerup(powerupsMapa[i]);
              powerupsMapa.erase(powerupsMapa.begin()+i);
            }
          }

          //Si colisiona con el kit y no esta cogido, lo coge
          if (col->collidesWith(jugador1->getSprite(), kit) && !kitCogido)
          {
            jugador1->setKit(kit);
            kitCogido = true;
          }

          break;

        case sf::Keyboard::Left:
          //Guardamos la posicion actual del sprite
          oldPosSp = jugador1->getSprite()->getPosition();
          
          jugador1->getSprite()->move(-kVel, 0);
          jugador1->getSprite()->setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
          //Reflejo vertical
          jugador1->getSprite()->setScale(-1, 1);

          //Si colisiona con alguna arma se coge
          for (unsigned int i = 0; i < armasMapa.size(); i++)
          {
            if (col->collidesWith(jugador1->getSprite(), armasMapa[i]->getSprite()))
            {
              jugador1->setArma(armasMapa[i]);
              armasMapa.erase(armasMapa.begin()+i);
            }
          }

          //Si colisiona con algun power-up se coge
          for (unsigned int i = 0; i < powerupsMapa.size(); i++)
          {
            if (col->collidesWith(jugador1->getSprite(), powerupsMapa[i]->getSprite()))
            {
              jugador1->setPowerup(powerupsMapa[i]);
              powerupsMapa.erase(powerupsMapa.begin()+i);
            }
          }

          //Si colisiona con el kit y no esta cogido, lo coge
          if (col->collidesWith(jugador1->getSprite(), kit) && !kitCogido)
          {
            jugador1->setKit(kit);
            kitCogido = true;
          }

          break;

        case sf::Keyboard::Up:
          //Guardamos la posicion actual del sprite
          oldPosSp = jugador1->getSprite()->getPosition();

          jugador1->getSprite()->move(0, -kVel);
          jugador1->getSprite()->setTextureRect(sf::IntRect(0 * 75, 3 * 75, 75, 75));

          //Si colisiona con alguna arma se coge
          for (unsigned int i = 0; i < armasMapa.size(); i++)
          {
            if (col->collidesWith(jugador1->getSprite(), armasMapa[i]->getSprite()))
            {
              jugador1->setArma(armasMapa[i]);
              armasMapa.erase(armasMapa.begin()+i);
            }
          }

          //Si colisiona con algun power-up se coge
          for (unsigned int i = 0; i < powerupsMapa.size(); i++)
          {
            if (col->collidesWith(jugador1->getSprite(), powerupsMapa[i]->getSprite()))
            {
              jugador1->setPowerup(powerupsMapa[i]);
              powerupsMapa.erase(powerupsMapa.begin()+i);
            }
          }

          //Si colisiona con el kit y no esta cogido, lo coge
          if (col->collidesWith(jugador1->getSprite(), kit) && !kitCogido)
          {
            jugador1->setKit(kit);
            kitCogido = true;
          }

          break;

        case sf::Keyboard::Down:
          //Guardamos la posicion actual del sprite
          oldPosSp = jugador1->getSprite()->getPosition();

          jugador1->getSprite()->move(0, kVel);
          jugador1->getSprite()->setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));

          //Si colisiona con alguna arma se coge
          for (unsigned int i = 0; i < armasMapa.size(); i++)
          {
            if (col->collidesWith(jugador1->getSprite(), armasMapa[i]->getSprite()))
            {
              jugador1->setArma(armasMapa[i]);
              armasMapa.erase(armasMapa.begin()+i);
            }
          }

          //Si colisiona con algun power-up se coge
          for (unsigned int i = 0; i < powerupsMapa.size(); i++)
          {
            if (col->collidesWith(jugador1->getSprite(), powerupsMapa[i]->getSprite()))
            {
              jugador1->setPowerup(powerupsMapa[i]);
              powerupsMapa.erase(powerupsMapa.begin()+i);
            }
          }

          //Si colisiona con el kit y no esta cogido, lo coge
          if (col->collidesWith(jugador1->getSprite(), kit) && !kitCogido)
          {
            jugador1->setKit(kit);
            kitCogido = true;
          }

          break;

        case sf::Keyboard::Enter:
          if(!jugador1->getKit())
          {
            if(instanceof<Magia>(jugador1->getArma())){
              disparoBola = static_cast<Magia*>(jugador1->getArma())->disparar(jugador1->getSprite()->getPosition());
            }
            else if(instanceof<Espada>(jugador1->getArma())){
              jugador1->getSprite()->setTextureRect(sf::IntRect(1 * 75, 1 * 75, 75, 75));
            }
          }

          else
          {
            jugador1->setKit(nullptr);
            kitCogido = false;
          }
          
          break;

        case sf::Keyboard::RShift:
          if (jugador1->getPowerup())
          {
            //Si tenemos tipo 0 aumentamos la velocidad del juagador
            if (jugador1->getPowerup()->getTipo() == 0)
            {
              kVel = 15;
              jugador1->setPowerup(nullptr);
            }
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

    //****************************************** RENDER *******************************
    //*********************************************************************************

    //Limpiamos la pantalla
    window->clear();

    window->draw(*respawn_player_one);
    window->draw(*respawn_player_two);

    //Dibujamos al jugador
    window->draw(*jugador1->getSprite());

    //Dibujamos las armas del mapa
    for (unsigned int i = 0; i < armasMapa.size(); i++)
    {
      window->draw(*armasMapa[i]->getSprite());
    }

    //Dibujamos los armas del mapa
    for (unsigned int i = 0; i < powerupsMapa.size(); i++)
    {
      window->draw(*powerupsMapa[i]->getSprite());
    }

    //Dibujamos el kit si no lo ha cogido nadie
    if(!kitCogido) window->draw(*kit);

    //Dibujamos y movemos el disparo si existe
    if(disparoBola) 
    {
      window->draw(*disparoBola->getSprite());
      disparoBola->mover();
    }
    //Mostramos en la ventana el dibujado
    window->display();
  }

  return 0;
}