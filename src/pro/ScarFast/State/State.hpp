#pragma once

struct Controller_t;

struct State_t {
    enum State_type {
        INGAME,     //En partida
        CREDITS,    //Creditos 
        INIT,       //Menu inicial
        MPLAY,       //Menú Jugar
        CONTROLS    //Controles del menu inicial
    };

    State_t(Controller_t* r) : renderEngine(r){}
    virtual ~State_t() = default;
    virtual void init()     = 0;
    virtual void getInput() = 0;
    virtual void update()   = 0;
    virtual void endScene() = 0;

protected:
    Controller_t* renderEngine {nullptr};
};
