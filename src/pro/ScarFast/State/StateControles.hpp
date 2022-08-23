#pragma once
#include "State.hpp"

struct StateControles : State_t {

public:
    StateControles(Controller_t* r) : State_t(r){}
    void init() override;
    void getInput() override;
    void update() override;
    void endScene() override;
};