#include "arma.hpp"
#include "disparo.hpp"
#include "../../Game.hpp"
#include "../facade/Controller.hpp"
#include "../facade/ControllerMan.hpp"

#define countdown 0.5f

// Constructor espada
Arma::Arma(int dmg, Sprite_t *spArma, float _cadencia) : damage(dmg), sp(spArma), tipoArma(TipoArma::espada), cadencia(_cadencia), cargas(1), max_cargas(1) {};

// Constructor magia
Arma::Arma(int dmg, Sprite_t *spArma, int tm, float v, int _cargas, int _max_cargas, float _cadencia) : damage(dmg), sp(spArma), tipoMagia(tm), velocity(v), tipoArma(TipoArma::magia), cargas(_cargas), max_cargas(cargas), cadencia(_cadencia) {};

//Destructor
Arma::~Arma() {};

Disparo* Arma::disparar(Player_t* p){
    std::string textura = "resources/bola.png";

    //Y creo el spritesheet a partir de la imagen anterior
    Physics_t* phy = new Physics_t();
    Sprite_t* spBola = new Sprite_t(textura, 32 , 32 ,phy);
    spBola->setRoute(textura);
    //Le pongo el centroide donde corresponde
    //Cojo el sprite que me interesa por defecto del sheet

    // Lo dispongo en el centro de la pantalla
    spBola->getPhysics()->x = p->getSprite()->getPhysics()->x;
    spBola->getPhysics()->y = p->getSprite()->getPhysics()->y;

    Disparo *disparo = nullptr;

    if(p->getID() == ID_PLAYER_ONE) {
        disparo = new Disparo(spBola, damage, tipoMagia, velocity, *p->getDireccion(), Objetivo::player_two);
    }else{
        disparo = new Disparo(spBola, damage, tipoMagia, velocity, *p->getDireccion(), Objetivo::player_one);
    }

    ControllerMan::instancia().controller().createShoot(disparo->getEntity(), spBola);
    //disparo->mover();
    return disparo;
}

void Arma::recargar() {
    if(cargas < max_cargas)
    {
        if(recarga == 0.f)
        {
            recarga = ControllerMan::instancia().controller().getTimeElapsed() + cadencia;
        }
        else if(ControllerMan::instancia().controller().getTimeElapsed() >= recarga)
        {
            recarga = 0.f;
            cargas++;
        }
    }
}

Sprite_t* Arma::getSprite() {
    return sp;
}

void Arma::setSprite(Sprite_t* sprite){
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

int Arma::getCargas() {
    return cargas;
}

void Arma::setCargas(int _carga) {
    cargas = _carga;
}

int Arma::getMaxCargas() {
    return max_cargas;
}

void Arma::setMaxCargas(int _maxCarga) {
    max_cargas = _maxCarga;
}

float Arma::getCadencia() {
    return cadencia;
}

void Arma::setCadencia(float _cadencia){
    cadencia = _cadencia;
}

float Arma::getTimeCountdown() {
    return timeCountdown;
}

void Arma::updateTimeCountdown() {
    timeCountdown = ControllerMan::instancia().controller().getTimeElapsed() + countdown;
}

void Arma::setTimeCountdown(float t) {
    timeCountdown = t;
}
