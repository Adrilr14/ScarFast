#include "disparo.hpp"
#include "player.hpp"
#include "../../facade/ControllerMan.hpp"
#include "../../facade/Controller.hpp"
#include <iostream>

Disparo::Disparo( Sprite_t *spDisparo, int damage, int tipo, float v, Direction_t d, Objetivo o) : spDisparo(spDisparo), damage(damage), tipo(tipo), vel(v), direccion(d), objet(o) {}

Disparo::~Disparo() {}

void Disparo::mover() {
    if(direccion.dir == -1){
        direccion.dir = 1;
    }
    if(this != nullptr && spDisparo->getPhysics()->calcularCollisionDisparo(this) == false){
        spDisparo->getPhysics()->x += direccion.getValuesDirection(direccion.dir).m_x * vel * ControllerMan::instancia().controller().getDeltaTime();
        spDisparo->getPhysics()->y += direccion.getValuesDirection(direccion.dir).m_y * vel * ControllerMan::instancia().controller().getDeltaTime();
        ControllerMan::instancia().controller().shoot(entityID,spDisparo->getPhysics()->x,spDisparo->getPhysics()->y);
    }else{
        //std::cout << Map_Disparos::disparos.size() << std::endl;
        ControllerMan::instancia().controller().destroyShoot(entityID);
        //auto* aux = Map_Disparos::disparos[entityID];
        //Map_Disparos::disparos.erase(entityID);
        //std::cout << Map_Disparos::disparos.size() << std::endl;
        //delete aux;
        //aux = nullptr;
    }
}

Sprite_t* Disparo::getSprite() {
    return spDisparo;
}

int Disparo::getDamage() {
    return damage;
}

void Disparo::setDamage(int d) {
    damage = d;
}