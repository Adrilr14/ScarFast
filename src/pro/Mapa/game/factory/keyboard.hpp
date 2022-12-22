#pragma once

struct Keyboard_t {
    /* Keyboard con teclas comunes para ambos jugadores */

    bool button_escape      { false };
    ////////////////////////////////
    //Player 1
    bool button_W           { false };
    bool button_A           { false };
    bool button_S           { false };
    bool button_D           { false };

    ////////////////////////////////
    //Player 2
    bool button_Up          { false };
    bool button_Down        { false };
    bool button_Left        { false };
    bool button_Right       { false };

    Keyboard_t(){};
    ~Keyboard_t(){};
};