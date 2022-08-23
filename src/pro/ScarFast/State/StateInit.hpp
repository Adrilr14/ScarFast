#pragma once
#include "State.hpp"

struct StateInit_t : State_t {

public:
    StateInit_t(Controller_t* r) : State_t(r){}
    void init() override;
    void getInput() override;
    void update() override;
    void endScene() override;
};