#include <iostream>
#include "player.hpp"
#include "arma.hpp"
#include "powerup.hpp"

Player::Player(sf::Sprite *sprite, int vida, Arma *arma) : sp(sprite), hp(vida), a(arma), power_up(nullptr), kit(nullptr), direccion(3) {}

Player::~Player() {}

sf::Sprite* Player::getSprite(){
    return sp;
}

void Player::setSprite(sf::Sprite *spriteSet){
    sp = spriteSet;
}

int Player::getHP() {
    return hp;
}

void Player::setHP(int vida) {
    hp = vida;
}

Arma* Player::getArma(){
    return a;
}

void Player::setArma (Arma *armaSet){
    a = armaSet; 
}

Powerup* Player::getPowerup() {
    return power_up;
}

void Player::setPowerup(Powerup *pow) {
    power_up = pow;
}

sf::Sprite* Player::getKit() {
    return kit;
}

void Player::setKit(sf::Sprite *sprite) {
    kit = sprite;
}

Direction_t Player::getDireccion() {
    return direccion;
}

void Player::setDireccion(int d){
    direccion = Direction_t(d);
}
