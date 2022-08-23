#pragma once
#include "State.hpp"

struct StateGame_t : State_t {

    float tiempo_transcurrido {0.0};
public:
    StateGame_t(Controller_t* r) : State_t(r){}
    void init() override;
    void getInput() override;
    void update() override;
    void endScene() override;
};