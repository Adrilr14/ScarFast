#pragma once
#include <string>

using Entity_ID = std::size_t;

//Vector para las posiciones y las direcciones
struct Vector2D{
    float m_x;
    float m_z;
    float angle;
};

/* Estado de los objetos: Son visibles o no**/
enum State_v { 
    visible, 
    hide
};

/** Estado de los jugadores **/
enum State {
    alive,
    dead
};