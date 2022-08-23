#include "ControllerMan.hpp"
#include "SfmlGraphics.hpp"

ControllerMan::ControllerMan() {
    m_motor = new SfmlGraphics();
}

ControllerMan::~ControllerMan() {
    delete m_motor;
}

Controller_t& ControllerMan::controller() {
    return *m_motor;
}

ControllerMan& ControllerMan::instancia() {
    static ControllerMan instance;
    return instance;
}