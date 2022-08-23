#pragma once
#include <string>

using EntityID_t = std::size_t;

struct Vector2D {
    int m_x;
    int m_y;
    int angle;
};

enum Personajes{
    minotauro = 0,
    golem = 1,
    enemigo3 = 2,
    enemigo2 = 3,
    enemigo1 = 4
};

enum Estado_Personaje{
    atacar,
    morir,
    andar,
    parado
};