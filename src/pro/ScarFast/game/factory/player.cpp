#include "player.hpp"
#include "powerup.hpp"
#include "../../facade/ControllerMan.hpp"
#include "../../facade/Controller.hpp"
#include "../Game.hpp"
#include <iostream>

#define inmunity_time 1.f
#define frameTime 0.05f
#define noGrabKit 1.5f

// Constructor
Player_t::Player_t(const char* route, int width, int height, Arma* _arma) : arma(_arma) {
        Physics_t* phy = new Physics_t();
        spr = new Sprite_t(route,width,height,phy);
        direccion = new Direction_t();
        hp = new Hp_t();

        sounds = new MainSound();
        sounds->activarShortSound("movimiento", new Buffer("resources/sounds/movimiento.wav"), 5);
        sounds->activarShortSound("powerup", new Buffer("resources/sounds/PowerUp.wav"), 60);
        sounds->activarShortSound("ganarRonda", new Buffer("resources/sounds/winRound.wav"), 80);
        sounds->activarShortSound("pack", new Buffer("resources/sounds/pack.wav"), 60);
        sounds->activarShortSound("disparo", new Buffer("resources/sounds/disparo.wav"), 40);
        sounds->activarShortSound("empezarRonda", new Buffer("resources/sounds/StartRound.wav"), 50);
        sounds->activarShortSound("muerte", new Buffer("resources/sounds/muerte.wav"), 50);

    }

// Destructor
Player_t::~Player_t() {}

void Player_t::checkCollisions(){
    spr->getPhysics()->calcularCollisionPlayer(this);
    spr->getPhysics()->checkCollisionKit(this);
    spr->getPhysics()->checkCollisionRespawn(this);
    spr->getPhysics()->checkCollisionPowerUp(this);
    if(!receive_damage)
    {
        spr->getPhysics()->checkCollisionSpikes(this);
    }
    else
    {
        if(timeRecover == 0.f)
        {
            timeRecover = ControllerMan::instancia().controller().getTimeElapsed() + inmunity_time;
            nextColor = ControllerMan::instancia().controller().setColorPlayer(entityID, nextColor);
        }
        else
        {
            if(ControllerMan::instancia().controller().getTimeElapsed() >= timeRecover) {
                receive_damage = false;
                timeRecover = 0.f;
                nextColor = ControllerMan::instancia().controller().setColorPlayer(entityID, nextColor);
            }
        }
    }
}

MainSound* Player_t::getSonido(){
    return sounds;
}

void Player_t::powerUpUsed() {
    if(powerUp != nullptr) {
        if(tiempo_transcurrido == 0.0) {
            tiempo_transcurrido = ControllerMan::instancia().controller().getTimeElapsed() + 5.f;
        }
        if(tiempo_transcurrido <= ControllerMan::instancia().controller().getTimeElapsed()) {
            powerUp->disabled_PowerUp(this);
            //delete powerUp;
            powerUp = nullptr;
            tiempo_transcurrido = 0.0;
        }
    }   
}

Sprite_t* Player_t::getSprite() {
    return spr;
}

Direction_t* Player_t::getDireccion() {
    return direccion;
}

Arma* Player_t::getArma(){
    return this->arma;
}

EntityID_t Player_t::getID() {
    return entityID;
}

Disparo* Player_t::getDisparo(){
    return disparo;
}

Sprite_t* Player_t::getKit() {
    return kit;
}

Power_Up* Player_t::getPowerUp() {
    return powerUp;
}

Hp_t* Player_t::getHp() {
    return hp;
}

void Player_t::setHp(Hp_t* vida) {
    hp = vida;
}

Personajes Player_t::getPersonaje() {
    return pers;
}

void Player_t::setPersonaje(Personajes personaje){
    pers = personaje;
}

Estado_Personaje Player_t::getEstado(){
    return estado;
}

bool Player_t::getInvulnerable() {
    return invulnerable;
}

bool Player_t::getReceive_damage() {
    return receive_damage;
}

void Player_t::setArma(Arma* a){
    this->arma = a;
}


void Player_t::setDisparo(Disparo* d){
    //sounds->play("disparo");
    //this->disparo = d;
}

void Player_t::setKit(Sprite_t* k) {
    kit = k;
}

void Player_t::setPowerUp(Power_Up* pw) {
    powerUp = pw;
}

void Player_t::setInvulnerable(bool v) {
    invulnerable = v;
}

void Player_t::setReceive_damage(bool r) {
    receive_damage = r;
}

void Player_t::setEstado(Estado_Personaje s) {
    if(estado != s && estado != Estado_Personaje::morir && estado != Estado_Personaje::atacar){
        estado = s;
        spr->frame_r = 0;  
    } 
}

void Player_t::setEstado_after_dead(Estado_Personaje s){
    estado = s;
}

float Player_t::getTimeAnimation() {
    return timeAnimation;
}

void Player_t::updateTimeAnimation() {
    timeAnimation = ControllerMan::instancia().controller().getTimeElapsed() + frameTime;
}

void Player_t::setTimeAnimation(float newTime) {
    timeAnimation = newTime;
}

float Player_t::getTimeKit() {
    return timeKit;
}

void Player_t::updateTimeKit() {
    timeKit = ControllerMan::instancia().controller().getTimeElapsed() + noGrabKit;
}

void Player_t::setTimeKit(float newTime) {
    timeKit = newTime;
}
