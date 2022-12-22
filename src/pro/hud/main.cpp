#include <SFML/Graphics.hpp>
#include <iostream>
#include "ej_modulos/hud.h"
#include "include/config.h"
#include "ej_modulos/sys/collision.hpp"
#include "ej_modulos/game/magia.hpp"
#include "ej_modulos/game/espada.hpp"
#include "ej_modulos/game/player.hpp"
#include "ej_modulos/game/disparo.hpp"
#include "ej_modulos/game/powerup.hpp"


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
  int kVel=5;
  //Creamos una ventana
  sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(640, 480), "HUD");
  Hud *hud=new Hud();

  Disparo *disparoBola = nullptr;

  std::vector<Arma*> armasMapa; //Array para comprobar las colisiones con las armas del mapa
  std::vector<Powerup*> powerupsMapa; //Array para comprobar las colisiones con los powerups del mapa

  //Creamos un objeto Collsion para detectar colisiones
  Collision *col = new Collision();
  int aux=0;
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
  sf::Sprite* sprite = createSprite("sprites.png", sf::Vector2f(320.f, 240.f), 75, 75, 0, 0);
  Player *jugador1 = new Player(sprite, espada);

  //Creamos powerup
  sf::Sprite* spPowerup = createSprite("crate_powerup.png", sf::Vector2f(480.f, 360.f), 20, 30, 0, 0);
  Powerup *pow1 = new Powerup(1, spPowerup, 0, 5);

  //Creamos el kit
  sf::Sprite* kit = createSprite("brick_1.png", sf::Vector2f(160.f, 360.f), 20, 30, 0, 0);
  bool kitCogido = false;

  //Metemos la magia en el array de armas del mapa
  armasMapa.push_back(magia);

  //Metemos el power-up en el array de

  //Creamos un vector para guardar la posicion del sprite powerups
  powerupsMapa.push_back(pow1);
  sf::Vector2f oldPosSp (0.f, 0.f);

  //Bucle del juego
  while (window->isOpen()) {
      sf::Event event;
      while (window->pollEvent(event)) {
        switch (event.type) {
          case sf::Event::Closed:
            window->close();
          case sf::Event::KeyPressed:
          switch (event.key.code) {
            case sf::Keyboard::Escape:
              window->close();
              break;
            case sf::Keyboard::Space:
              hud->bajarVida(10);
            break;
            case sf::Keyboard::Right:
              oldPosSp = jugador1->getSprite()->getPosition();

              jugador1->getSprite()->move(kVel, 0);
              jugador1->getSprite()->setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
              //Escala por defecto
              jugador1->getSprite()->setScale(1, 1);

              //Si colisiona con alguna arma se coge
              for (unsigned int i = 0; i < armasMapa.size(); i++){
                if (col->collidesWith(jugador1->getSprite(), armasMapa[i]->getSprite())){
                  jugador1->setArma(armasMapa[i]);
                  armasMapa.erase(armasMapa.begin()+i);
                  aux=1;
                }
              }

              //Si colisiona con algun power-up se coge
              for (unsigned int i = 0; i < powerupsMapa.size(); i++){
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
              for (unsigned int i = 0; i < armasMapa.size(); i++){
                if (col->collidesWith(jugador1->getSprite(), armasMapa[i]->getSprite())){
                  jugador1->setArma(armasMapa[i]);
                  armasMapa.erase(armasMapa.begin()+i);
                  aux=1;
                }
              }

              //Si colisiona con algun power-up se coge
              for (unsigned int i = 0; i < powerupsMapa.size(); i++){
                if (col->collidesWith(jugador1->getSprite(), powerupsMapa[i]->getSprite()))
                {
                  jugador1->setPowerup(powerupsMapa[i]);
                  powerupsMapa.erase(powerupsMapa.begin()+i);
                }
              }

              //Si colisiona con el kit y no esta cogido, lo coge
              if (col->collidesWith(jugador1->getSprite(), kit) && !kitCogido){
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
                  aux=1;
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
                  aux=1;
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

            default:
              std::cout << event.key.code << std::endl;
            break;
          }
        }
      }
      window->clear();
      hud->dibujarCorazon(*window);
      if(aux!=0){
        hud->pintarObjeto(aux, *window);
      }
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

      window->display();
  }

  return 0;
}