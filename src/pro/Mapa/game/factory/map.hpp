#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include "sprite.hpp"

class Map_t {
    /**Clase para poder cargar el mapa**/
public:
    /**Funciones publicas**/
    Map_t(){};
    ~Map_t();
    void Load_Map();

    /**Getters**/
    auto getWithMap() { return widthMap; }
    auto getHeightMap() { return heightMap; }
    auto getMatrizMapa() { return mapaMatrix; }
private:
    int widthMap    {0};
    int heightMap   {0};
    std::vector<std::vector<Sprite_t*>> mapaMatrix;
};