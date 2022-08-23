#include "StateMenuPlay.hpp"
#include "../facade/Controller.hpp"

void StateMenuPlay::init(){
    renderEngine->initMenuJugar();
}

void StateMenuPlay::getInput() {
    renderEngine->getInputMenuJugar();
}

void StateMenuPlay::update() {
    renderEngine->updateMenuJugar();
}

void StateMenuPlay::endScene(){
}