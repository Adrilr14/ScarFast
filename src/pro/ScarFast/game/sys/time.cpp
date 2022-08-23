#include "time.hpp"
#include "../../facade/Controller.hpp"
#include "../../facade/ControllerMan.hpp"
#include "../../Game.hpp"
#include <iostream>


void Temporizador_t::startCounting() {
    if(aux == -1){
        aux = ControllerMan::instancia().controller().getTemporizador();
    }
    //std::cout << ControllerMan::instancia().controller().getTemporizador() << std::endl;
    if(ControllerMan::instancia().controller().getTemporizador() >= aux+segundo){
        segundo = 0;
    }
}

void Temporizador_t::getTime() {
    aumentoTiempo += ControllerMan::instancia().controller().getDeltaTime();

    if(aumentoTiempo >= 1.f) {
        aumentoTiempo = 0.f;
        segundo--;
        ControllerMan::instancia().controller().showTemporizador(minuto,segundo);
        ControllerMan::instancia().controller().resetTemporizador();
        if(segundo <= 0) {
            if(minuto > 0){
            minuto--;
            segundo = 59;
            }else{
                if(aux == SET_UP_FOR_GAME){
                    Game_t::getInstance()->setGameStart(true);
                }
            }
        }
    }
}

bool Temporizador_t::still_time_to_process() {
    if(minuto > 0 || segundo > 0){
        return true;
    }
    aux = -1;
    return false;
}