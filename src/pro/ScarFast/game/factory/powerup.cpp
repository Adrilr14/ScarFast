#include <ctime>
#include "powerup.hpp"
#include "../../Game.hpp"
#include "../../facade/ControllerMan.hpp"
#include <random>
#include <iostream>

void Power_Up::create_powerUp_for_the_map() {
    Power_Up::reset_activate_values();

    auto& pw = Game_t::getInstance()->getMap()->getPowerUps();
    //std::cout << "POWERUP: " << pw.size() << std::endl;

    std::srand(std::time(nullptr));

    for(unsigned int i = 0; i < pw.size(); i++){
        if(examinar > 1) break;
        unsigned int random = 0 + (rand()%((pw.size()-1)-0));
        if(random < pw.size() && pw[random]->activate == false){
            std::random_device device;
            std::mt19937 generador(device());
            std::discrete_distribution<> distribucion({30, 50, 50, 30, 5});
            switch (distribucion(generador)){
            case 0:
                pw[random]->setCategory(Category_t::increase_speed);
                break;
            case 1:
                pw[random]->setCategory(Category_t::spikes);
                break;
            case 2:
                pw[random]->setCategory(Category_t::shield);
                break;
            case 3:
                pw[random]->setCategory(Category_t::decrease_speed);
                break;
            case 4:
                pw[random]->setCategory(Category_t::invunerabilty);
                break;
            
            default:
                break;
            }
            pw[random]->setActivate(true);
            pw[random]->spr->setVisible(State_v::visible);
            examinar++;
        }
    }
}

void Power_Up::reset_activate_values() {
    auto& pw = Game_t::getInstance()->getMap()->getPowerUps();

    for(unsigned int i = 0; i < pw.size(); i++){
        if(pw[i] != nullptr) {
            pw[i]->activate = false;
            if(pw[i]->spr != nullptr){
                pw[i]->spr->setVisible(State_v::hidden);
            }
        }
    }
}

void Power_Up::use_power_up(Player_t* p) {
    temporizador = new Temporizador_t(tiempo_item);
    switch (type) {
    case Category_t::increase_speed:
        //Incrementamos la velocidad del usuario
        p->getSprite()->getPhysics()->velx += INCREMENT_SPEED;
        p->getSprite()->getPhysics()->vely += INCREMENT_SPEED;
        break;
    case Category_t::spikes:
        if(p->getID() == ID_PLAYER_ONE) {
            ControllerMan::instancia().controller().create_spikes_p_one();
        }else{
            ControllerMan::instancia().controller().create_spikes_p_two();
        }
        //Aun por hacer tengo q poner los objetos en el mapa
        break;
    case Category_t::shield:
        p->getHp()->setShield(SHIELD);

        break;
    case Category_t::decrease_speed:
        if(p->getID() == ID_PLAYER_ONE) {
            Game_t::getInstance()->getPlayerTwo()->getSprite()->getPhysics()->velx -= INCREMENT_SPEED;
            Game_t::getInstance()->getPlayerTwo()->getSprite()->getPhysics()->vely -= INCREMENT_SPEED;
        }else{
            Game_t::getInstance()->getPlayerOne()->getSprite()->getPhysics()->velx -= INCREMENT_SPEED;
            Game_t::getInstance()->getPlayerOne()->getSprite()->getPhysics()->vely -= INCREMENT_SPEED;
        }
        break;
    case Category_t::invunerabilty:
        p->getHp()->setVulnerabilidad(true);
        
        break;
    
    default:
        break;
    }
}

void Power_Up::disabled_PowerUp(Player_t* p) {

    //std::cout << "Se ha acabado el tiempo" << std::endl;

    switch (type) {
    
    case Category_t::increase_speed:
        //Incrementamos la velocidad del usuario
        p->getSprite()->getPhysics()->velx -= INCREMENT_SPEED;
        p->getSprite()->getPhysics()->vely -= INCREMENT_SPEED;
        break;
    case Category_t::spikes:
        ControllerMan::instancia().controller().destroy_spikes(p->getID());
        break;
    case Category_t::shield:
        //p->getHp()->setShield(0);
        break;
    case Category_t::decrease_speed:
        if(p->getID() == ID_PLAYER_ONE) {
            Game_t::getInstance()->getPlayerTwo()->getSprite()->getPhysics()->velx += INCREMENT_SPEED;
            Game_t::getInstance()->getPlayerTwo()->getSprite()->getPhysics()->vely += INCREMENT_SPEED;
        }else{
            Game_t::getInstance()->getPlayerOne()->getSprite()->getPhysics()->velx += INCREMENT_SPEED;
            Game_t::getInstance()->getPlayerOne()->getSprite()->getPhysics()->vely += INCREMENT_SPEED;
        }
        break;
    case Category_t::invunerabilty:

        p->getHp()->setVulnerabilidad(false);
        
        break;
    
    default:
        break;
    }  
    //p->setPowerUp(nullptr);  
}