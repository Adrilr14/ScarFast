#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "include/config.h"
#include "ej_modulos/golem.h"
#include "ej_modulos/minotauro.h"
#include <string>
#include <sstream>

#define kVel 5
#define kVel2 4.5


int main() {

  sf::Clock time;
  sf::Text texto;
  std::ostringstream sol;
  sf::Font cibeles;
  int aux=0;
  int minuto=0; // CONTROLADOR DE MINUTOS
  int segundo=6;  //CONTROLADOR DE SEGUNDOS
  int msegundo=60;
  int fin=0;
  sf::Sound sonido;
  sf::SoundBuffer buffer;

  if(!buffer.loadFromFile("resources/fin.wav")){

      std::cout << "En paz descanse el sonido";
  }

  
  sonido.setBuffer(buffer);
  cibeles.loadFromFile("resources/alarmclock.ttf");

  golem *gol = new golem();
  minotauro *min = new minotauro();

  //Creamos una ventana
  sf::RenderWindow window(sf::VideoMode(640, 480), "Movimiento flow");
  window.setFramerateLimit(60);

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


    //SONIDO

    if(segundo == 6){
        sonido.play();
    }


    //Temporizador
    
    texto.setFont(cibeles);
    aux=int(time.getElapsedTime().asSeconds());

    


    texto.setString(std::to_string(minuto) + ":" + std::to_string(segundo));


    if(fin==0){
      msegundo--;

      if(segundo==0 && minuto>=0){
        minuto--;
        segundo=59;;
      }
      
      if(msegundo==0){
        segundo--;
        msegundo=60;
      }

    }
    

    if(segundo<=10 && minuto==0 && msegundo%2!=0){
          texto.setColor(sf::Color::Red); //Para ultimos segundos
          texto.setScale(1,1);
          texto.setPosition(275,100);

    }else if(msegundo%2==0 && segundo<=10 && minuto==0){
          texto.setColor(sf::Color::Red); //Para ultimos segundos
          texto.setScale(1.05,1.05);
          texto.setPosition(275,100);

    }else{
          texto.setColor(sf::Color::White);
          texto.setScale(1,1);
          texto.setPosition(275,100);

    }

    if(minuto==0 && segundo==0){
      fin++;
    }

    

    if(fin==600){
      window.close();


    }else{
    gol->update();
    min->update();

    window.clear();
    window.draw(gol->getSprite());
    window.draw(min->getSprite());

    if(fin!=0){
      texto.setString("FIN DE LA PARTIDA");
      texto.setColor(sf::Color::White);
      texto.setPosition(170,100);
      texto.setScale(1,1);
    }
    window.draw(texto);
    window.display();
    }


  


  
  }

  return 0;
}