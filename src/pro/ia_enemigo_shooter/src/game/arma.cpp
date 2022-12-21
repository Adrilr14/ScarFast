#include <iostream>
#include "arma.hpp"
#include "disparo.hpp"
#include "player.hpp"

// Constructor espada
Arma::Arma(int n, int dmg, sf::Sprite *spArma) : id(n), damage(dmg), sp(spArma), tipoArma(TipoArma::espada) {};

// Constructor magia
Arma::Arma(int n, int dmg, sf::Sprite *spArma, int tm, float v) : id(n), damage(dmg), sp(spArma), tipoMagia(tm), velocity(v), tipoArma(TipoArma::magia) {};

//Destructor
Arma::~Arma() {};

Disparo* Arma::disparar(Player *p){
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
    Disparo *disparo = new Disparo(1, spBola, damage, tipoMagia, velocity, p, p->getDireccion());
    //disparo->mover();
    return disparo;
}

sf::Sprite* Arma::getSprite() {
    return sp;
}

void Arma::setSprite(sf::Sprite* sprite){
    sp = sprite;
}

int Arma::getDamage() {
    return damage;
}

void Arma::setDamage(int d) {
    damage = d;
}

int Arma::getTipoMagia() {
    return tipoMagia;
}

void Arma::setTipoMagia(int tm) {
    tipoMagia = tm;
}

float Arma::getVelocity() {
    return velocity;
}

void Arma::setVelocity(float v) {
    velocity = v;
}

int Arma::getTipoArma() {
    return tipoArma;
}

void Arma::setTipoArma(int ta) {
    tipoArma = ta;
}
