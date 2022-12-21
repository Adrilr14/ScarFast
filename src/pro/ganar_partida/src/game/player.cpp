#include "player.hpp"
#include <iostream>

Player::Player(sf::Sprite *sprite, Arma *arma) : sp(sprite), a(arma), power_up(nullptr), kit(nullptr) {}

Player::~Player() {}

sf::Sprite* Player::getSprite(){
    return sp;
}

void Player::setSprite(sf::Sprite *spriteSet){
    sp = spriteSet;
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
