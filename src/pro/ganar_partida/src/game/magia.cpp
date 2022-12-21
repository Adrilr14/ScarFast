#include "magia.hpp"
#include <iostream>
#include "player.hpp"

Magia::Magia(int id, int damage, sf::Sprite *spArma) : Arma(id, damage, spArma) {}

Magia::~Magia() {}

Disparo* Magia::disparar(sf::Vector2f posPlayer){
    sf::Texture *tex = new sf::Texture;
    if (!(tex->loadFromFile("resources/bola.png"))) {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }

    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite *spBola = new sf::Sprite(*tex);

    //Le pongo el centroide donde corresponde
    spBola->setOrigin(64, 64);
    //Cojo el sprite que me interesa por defecto del sheet
    spBola->setTextureRect(sf::IntRect(0*64,0*64, 64, 64));

    // Lo dispongo en el centro de la pantalla
    spBola->setPosition(posPlayer.x+37.5, posPlayer.y);
    Disparo *disparo = new Disparo(1, spBola, 10, 1, 1);
    disparo->mover();
    return disparo;
}