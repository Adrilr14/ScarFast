#pragma once
#include <iostream>
#include "player.hpp"

class Hud{
    private:
        std::string route;
        std::map<std::string, std::pair<double,double>> hud_items{}; //Aqui tengo todos los items con sus posiciones
    public:
        Hud(std::string r, std::map<std::string, std::pair<double,double>> _hd);
        void display_hud();

        std::vector<std::tuple<int,int,int,int>> posiciones_ {
            std::make_tuple<int,int,int,int>(32,32,0,0),
            std::make_tuple<int,int,int,int>(32,32,32,0),
            std::make_tuple<int,int,int,int>(32,32,64,0),
            std::make_tuple<int,int,int,int>(32,32,96,0),
            std::make_tuple<int,int,int,int>(32,32,128,0),
            std::make_tuple<int,int,int,int>(32,32,160,0),
            std::make_tuple<int,int,int,int>(30,30,192,0),
            std::make_tuple<int,int,int,int>(30,30,222,0),
            std::make_tuple<int,int,int,int>(30,30,252,0),
            std::make_tuple<int,int,int,int>(32,32,298,0),
            std::make_tuple<int,int,int,int>(32,32,312,0),
            std::make_tuple<int,int,int,int>(32,32,332,0),
        };

        std::map<Category_t,int> powerUps_hud {
            { Category_t::decrease_speed, 1 },
            { Category_t::shield, 2 },
            { Category_t::spikes, 3 },
            { Category_t::increase_speed, 4 },
            { Category_t::invunerabilty, 5 }
        };

        std::map<int, std::tuple<int,int,int,int>> life_pl_one {
            {0 , posiciones_[6] },
            {1 , posiciones_[6] },
            {2 , posiciones_[6] },
            {3 , posiciones_[6] },
            {4 , posiciones_[6] }
        };

        std::map<int, std::tuple<int,int,int,int>> life_pl_two {
            {0 , posiciones_[6] },
            {1 , posiciones_[6] },
            {2 , posiciones_[6] },
            {3 , posiciones_[6] },
            {4 , posiciones_[6] }
        };

        void update();
        std::string getRoute();
        std::map<std::string,std::pair<double, double>> getHud_items(); 
};