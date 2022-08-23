#include "hud.hpp"
#include "../../facade/ControllerMan.hpp"
#include "../../Game.hpp"
#include <iostream> 

Hud::Hud(std::string r, std::map<std::string,std::pair<double,double>> hd) 
: route(r), hud_items(hd){}

void Hud::display_hud() {
    ControllerMan::instancia().controller().createHUD();
}

void Hud::update() {
    int hp_one = Game_t::getInstance()->getPlayerOne()->getHp()->getHp();
    int hp_two = Game_t::getInstance()->getPlayerTwo()->getHp()->getHp();
    hp_one /= 2;
    hp_two /= 2;
    unsigned int i = 0;
    for(i = 0; i < (hp_one / 10); i++ ){
        life_pl_one[i] = posiciones_[6];
    }
    if(i != 5) {
        if((int)((Game_t::getInstance()->getPlayerOne()->getHp()->getHp())/10) % 2 != 0) {
            life_pl_one[i++] = posiciones_[7];
        }
    }

    int escudo = Game_t::getInstance()->getPlayerOne()->getHp()->getShield();
    escudo =  escudo / 2;
    escudo = escudo / 10;
    if(escudo > 0) {
        for(int j = i; j < life_pl_one.size(); j++){
            if(escudo > 0){
                if(life_pl_one[j] == posiciones_[8] || life_pl_one[j] == posiciones_[9]) {
                    life_pl_one[j] = posiciones_[9];
                    escudo--;
                    i++;
                }
            }
        }
    }
    for(int j = i; j < life_pl_one.size(); j++){
        life_pl_one[j] = posiciones_[8];
    }

    int escudo_2 = Game_t::getInstance()->getPlayerTwo()->getHp()->getShield();
    escudo_2 =  escudo_2 / 2;
    escudo_2 = escudo_2 / 10;
    i = 0;
    for(i = 0; i < (hp_two / 10); i++ ){
        life_pl_two[i] = posiciones_[6];
    }
    if(i != 5) {
        if((int)((Game_t::getInstance()->getPlayerTwo()->getHp()->getHp())/10) % 2 != 0) {
            life_pl_two[i++] = posiciones_[7];
        }
    }

    if(escudo_2 > 0) {
        for(int j = i; j < life_pl_two.size(); j++){
            if(escudo_2 > 0){
                if(life_pl_two[j] == posiciones_[8] || life_pl_two[j] == posiciones_[9]) {
                    life_pl_two[j] = posiciones_[9];
                    escudo_2--;
                    i++;
                }
            }
        }
    }

    for(int j = i; j < life_pl_two.size(); j++){
        life_pl_two[j] = posiciones_[8];
    }

    ControllerMan::instancia().controller().updateHUD();
}

std::string Hud::getRoute() {
    return route;
}

std::map<std::string,std::pair<double, double>> Hud::getHud_items(){
    return hud_items;
}