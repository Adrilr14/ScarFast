#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/config.h"

#include "src/sys/collision.hpp"
#include "src/game/arma.hpp"
#include "src/game/player.hpp"
#include "src/game/disparo.hpp"
#include "src/game/powerup.hpp"
#include "src/game/enemy.hpp"
#include "src/sys/ia.hpp"
//#define kVel 5


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

  Disparo *disparoBola = nullptr;

  std::vector<Arma*> armasMapa; //Array para comprobar las colisiones con las armas del mapa
  std::vector<Powerup*> powerupsMapa; //Array para comprobar las colisiones con los powerups del mapa

  //Creamos un objeto Collsion para detectar colisiones
  Collision *col = new Collision();

  //Creamos una ventana
  sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(640, 480), "Colisiones");
  
  //Creamos magia
  int idMagia = 1;
  int damageMagia = 10;
  int tipoMagia = 0;
  float velocityMagia = 0.06;
  sf::Sprite* spMagia = createSprite("bola.png", sf::Vector2f (160.f, 120.f), 64, 64, 0, 0);
  Arma *magia = new Arma(idMagia, damageMagia, spMagia, tipoMagia, velocityMagia);

  //Creamos espada
  int idEspada = 1;
  int damageEspada = 10;
  sf::Sprite* spEspada = createSprite("sprites.png", sf::Vector2f(0.f, 0.f), 75, 75, 1, 1);
  Arma *espada = new Arma(idEspada, damageEspada, spEspada);

  //Creamos player
  sf::Sprite* spritePlayer1 = createSprite("sprites.png", sf::Vector2f(320.f, 240.f), 75, 75, 0, 0);
  int vidaPlayer1 = 100;
  Player *jugador1 = new Player(spritePlayer1, vidaPlayer1, espada);

  //Creamos enemigo
  //creamos la ia, rectangulo, sprite
  sf::RectangleShape *rectangle = new sf::RectangleShape(sf::Vector2f(150.f,150.f));
  rectangle->setOrigin(150 / 2, 150 / 2);
  IA *iaEnemy2 = new IA(rectangle, TipoIA::pursuit); 
  sf::Sprite* spEnemy = createSprite("sprites.png", sf::Vector2f(480.f, 360.f), 75, 75, 2, 2);
  Enemy *enemy = new Enemy(8, 10,3,.05f,spEnemy,iaEnemy2, sf::Vector2f(480.f, 360.f));
  rectangle->setPosition(enemy->getSprite()->getPosition());
  //Metemos la magia en el array de armas del mapa
  armasMapa.push_back(magia);

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
          oldPosSp = jugador1->getSprite()->getPosition();

          jugador1->getSprite()->move(kVel, 0);
          jugador1->getSprite()->setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
          //Escala por defecto
          jugador1->getSprite()->setScale(1, 1);
          //Cambiamos la direccion
          jugador1->setDireccion(1);

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

          break;

        case sf::Keyboard::Left:
          //Guardamos la posicion actual del sprite
          oldPosSp = jugador1->getSprite()->getPosition();
          
          jugador1->getSprite()->move(-kVel, 0);
          jugador1->getSprite()->setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
          //Reflejo vertical
          jugador1->getSprite()->setScale(-1, 1);
          //Cambiamos la direccion
          jugador1->setDireccion(2);

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

          break;

        case sf::Keyboard::Up:
          //Guardamos la posicion actual del sprite
          oldPosSp = jugador1->getSprite()->getPosition();

          jugador1->getSprite()->move(0, -kVel);
          jugador1->getSprite()->setTextureRect(sf::IntRect(0 * 75, 3 * 75, 75, 75));

          //Cambiamos la direccion
          jugador1->setDireccion(4);

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

          break;

        case sf::Keyboard::Down:
          //Guardamos la posicion actual del sprite
          oldPosSp = jugador1->getSprite()->getPosition();

          jugador1->getSprite()->move(0, kVel);
          jugador1->getSprite()->setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));

          //Cambiamos la direccion
          jugador1->setDireccion(3);

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

          break;

        case sf::Keyboard::Enter:
          if(!jugador1->getKit())
          {
            if(jugador1->getArma()->getTipoArma() == TipoArma::magia){
              disparoBola = jugador1->getArma()->disparar(jugador1);
            }
            else if(jugador1->getArma()->getTipoArma() == TipoArma::espada){
              jugador1->getSprite()->setTextureRect(sf::IntRect(1 * 75, 1 * 75, 75, 75));
            }
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

    if(disparoBola) 
    {
      disparoBola->mover();
    }

    //****************************************** RENDER *******************************
    //*********************************************************************************

    //Limpiamos la pantalla
    window->clear();

    //Dibujamos a los jugadores si su vida es superior a 0
    if (jugador1->getHP() > 0)
    {
      window->draw(*jugador1->getSprite());
    }

    //dibujamos al enemigo
    //window->draw(*rectangle);
    window->draw(*enemy->getSprite());
    enemy->moveEnemy(jugador1);
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

    //Dibujamos y movemos el disparo si existe
    if(disparoBola) 
    {
      window->draw(*disparoBola->getSprite());
    }

    //Mostramos en la ventana el dibujado
    window->display();
  }

  return 0;
}