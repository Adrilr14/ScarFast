#include "player.hpp"
#include <iostream>

Player::Player(sf::Sprite *sprite, Arma *arma) : sp(sprite), a(arma) {}

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