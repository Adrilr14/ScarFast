#include "StateControles.hpp"
#include "../facade/Controller.hpp"

void StateControles::init(){
    renderEngine->initMenuControles();
}

void StateControles::getInput() {
    renderEngine->getInputMenuControles();
}

void StateControles::update() {
    renderEngine->updateMenuControles();
}

void StateControles::endScene(){
}