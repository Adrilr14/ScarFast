#include "magia.hpp"
#include <iostream>

Magia::Magia(int id, int damage, sf::Sprite *spArma, int t, float v) : Arma(id, damage, spArma), tipo(t), vel(v) {}

Magia::~Magia() {}

Disparo* Magia::disparar(Player *p){
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
    spBola->setPosition(p->getSprite()->getPosition().x+37.5, p->getSprite()->getPosition().y);
    Disparo *disparo = new Disparo(1, spBola, damage, tipo, vel, p);
    //disparo->mover();
    return disparo;
}