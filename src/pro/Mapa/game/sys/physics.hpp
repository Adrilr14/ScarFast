#pragma once

#include <tuple>
#include <vector>

class Physics_t {

public:
    double x {0.0};
    double y {0.0};
    double velx {0.0};
    double vely {0.0};
    std::vector<std::pair<int,int>> cuadrante = 
    {   {-1,1}, {0,1}, {1,1},
        {-1,0}, {0,0}, {1,0},
        {-1,-1},{0,-1},{1,-1}      
    };
    Physics_t(){};
    Physics_t(double xvalue, double yvalue, double vx, double vy) 
    : x(xvalue), y(yvalue), velx(vx), vely(vy) {};

    ~Physics_t() {};
    
    std::tuple<int,int> getPosition();
    std::vector<std::pair<int,int>> calcularCuadrante(int x,int y);
};