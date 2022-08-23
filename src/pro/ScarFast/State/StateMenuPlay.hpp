#pragma once
#include "State.hpp"

struct StateMenuPlay : State_t {

public:
    StateMenuPlay(Controller_t* r) : State_t(r){}
    void init() override;
    void getInput() override;
    void update() override;
    void endScene() override;
};