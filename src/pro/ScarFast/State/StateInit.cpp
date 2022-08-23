#include "StateInit.hpp"
#include "../facade/Controller.hpp"

void StateInit_t::init(){
    renderEngine->initMenu();
}

void StateInit_t::getInput() {
    renderEngine->getInputMenu();
}

void StateInit_t::update() {
    renderEngine->updateMenu();
}

void StateInit_t::endScene(){

}