#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <map>
#include "sprite.hpp"
#include "powerup.hpp"

class Map_t {
    /**Clase para poder cargar el mapa**/
public:
    int number_mapa = 1;
    /**Funciones publicas**/
    Map_t(){};
    ~Map_t();
    void loadMap(int ruta);

    /**Getters**/
    auto getWithMap()       { return widthMap; }
    auto getHeightMap()     { return heightMap; }
    auto getRespawn_one()   { return respawn_player_one; }
    auto getRespawn_two()   { return respawn_player_two; }
    auto getKit()           { return kit; }
    auto& getKitOrigin()    { return kit_origin;}
    auto getMatrizMapa()    { return mapaMatrix; }
    auto& getPowerUps()     { return powerUps; }
    auto& getSpikes_1()     { return spikes_1; }
    auto& getSpikes_2()     { return spikes_2; }
    auto& getHud()          { return hud;}
    auto getEnemiesShoot()  { return es; }
    auto getEnemiesPatrol() { return epa; }
    auto getEnemiesPursuit(){ return epu; }
    auto getBackGround()    { return background; }
    

private:
    int widthMap    {0};
    int heightMap   {0};
    Sprite_t* respawn_player_one {nullptr};
    Sprite_t* respawn_player_two {nullptr};
    Sprite_t* kit {nullptr};
    std::pair<double,double> kit_origin;
    std::vector<Sprite_t*> spikes_1;
    std::vector<Sprite_t*> spikes_2;
    std::vector<Power_Up*> powerUps;
    std::vector<std::vector<std::pair<double,double>>> epa;
    std::vector<std::tuple<double,double,double,double>> es;
    std::vector<std::tuple<double,double,double,double>> epu;
    std::map<std::string,std::pair<double,double>> hud;
    std::vector<std::vector<Sprite_t*>> mapaMatrix;
    Sprite_t* background;
};