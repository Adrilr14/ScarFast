#include "StateGame.hpp"
#include "../Game.hpp"
#include "../facade/ControllerMan.hpp"
#include "../facade/Controller.hpp"
#include <iostream>

void StateGame_t::init(){
    Temporizador_t* t = new Temporizador_t(SET_UP_FOR_GAME);
    Game_t::getInstance()->setTemporizador(t);
}

void StateGame_t::getInput() {
    if(Game_t::getInstance()->getGameStart()){
        Physics_t::movePlayer();
    }
}

void StateGame_t::update() {
    renderEngine->run();
    auto* pl_one = Game_t::getInstance()->getPlayerOne();
    auto* pl_two = Game_t::getInstance()->getPlayerTwo();
     
    pl_one->checkCollisions(); // Comprobación recibir daño Player 1
    pl_two->checkCollisions(); // Comprobación recibir daño Player 2
    pl_one->getArma()->recargar(); // Recarga de los ataques Player 1
    pl_two->getArma()->recargar(); // Recarga de los ataques Player 2

    Physics_t::moveDisparo(); // Movimiento de los disparos

    // Comprobamos si los jugadores están muertos
    if(!pl_one->getHp()->is_alive()) {
        pl_one->setEstado(Estado_Personaje::morir);
        if(pl_one->getKit() != nullptr) {
            pl_one->getKit()->setVisible(State_v::visible);
            pl_one->getKit()->getPhysics()->x = pl_one->getSprite()->getPhysics()->x;
            pl_one->getKit()->getPhysics()->y = pl_one->getSprite()->getPhysics()->y;
            pl_one->updateTimeKit();
        }
        pl_one->setKit(nullptr);
        pl_one->getSonido()->play("muerte");
    }
    if(!pl_two->getHp()->is_alive()){   
        pl_two->setEstado(Estado_Personaje::morir);
        if(pl_two->getKit() != nullptr) {
            pl_two->getKit()->setVisible(State_v::visible);
            pl_two->getKit()->getPhysics()->x = pl_two->getSprite()->getPhysics()->x;
            pl_two->getKit()->getPhysics()->y = pl_two->getSprite()->getPhysics()->y;
            pl_two->updateTimeKit();
        }
        pl_two->setKit(nullptr);
        pl_two->getSonido()->play("muerte");
    }

    // Comprobamos si los jugadores están atacando con la maza
    if(pl_one->getEstado() == Estado_Personaje::atacar) {ControllerMan::instancia().controller().attackmele(pl_one);}
    if(pl_two->getEstado() == Estado_Personaje::atacar) {ControllerMan::instancia().controller().attackmele(pl_two);}

    auto enemigos = Game_t::getInstance()->getEnemies();
    for(unsigned int i = 0; i < enemigos.size(); i++) 
    {
        // Comprobación recibir daño enemigos
        enemigos[i]->checkReceive_damage();
        if(!enemigos[i]->getHp()->is_alive())
        {
            enemigos[i]->setEstado(Estado_Personaje::morir);
        }
    }

    if(Game_t::getInstance()->getRonda()->tryGanarPartida() == 0 ||
        Game_t::getInstance()->getRonda()->tryGanarPartida() == 1) {
            //std::cout << "Ha ganado un jugador " << std::endl;       
    }

    Game_t::getInstance()->getHud()->update();
    
    if(pl_one->getPowerUp() != nullptr && pl_one->getPowerUp()->getUsed() == true) {
        pl_one->powerUpUsed();
    }
    if(pl_two->getPowerUp() != nullptr && pl_two->getPowerUp()->getUsed() == true) {
        pl_two->powerUpUsed();
    }

    if(tiempo_transcurrido == 0.f) {
        tiempo_transcurrido = renderEngine->getTimeElapsed()+15.f;
    }
    if(tiempo_transcurrido <= renderEngine->getTimeElapsed()){
        Power_Up::setExaminar(0);
        Power_Up::create_powerUp_for_the_map();
        renderEngine->reset_power_ups();
        renderEngine->create_powerups_sfml();
        tiempo_transcurrido = 0.f;
    }    

    if(Game_t::getInstance()->getTemporizador() != nullptr) {
        Game_t::getInstance()->getTemporizador()->getTime();
    }
    pl_one->checkCollisions();
    pl_two->checkCollisions();

    renderEngine->updateGame(); // Renderizado
}

void StateGame_t::endScene(){
    
}