#pragma once

#include <tuple>
#include <vector>

#define TILES_WIDTH     20
#define TILES_HEIGHT    20

class Player_t;
class Sprite_t;
class Disparo;

class Physics_t {
    
public:

    double x {0.0};
    double y {0.0};
    double velx {180};
    double vely {180};
    std::vector<std::pair<int,int>> cuadrante = 
    {   {-1,-1}, {0,-1} , {1,-1},
        {-1,0},  {0, 0} , {1,0},
        {-1,1},  {0, 1} , {1,1}      
    };

    Physics_t(){};
    Physics_t(double xvalue, double yvalue, double vx, double vy) 
    : x(xvalue), y(yvalue), velx(vx), vely(vy) {};

    ~Physics_t() {};
    
    std::tuple<int,int> getPosition(Player_t* p);
    void calcularCollisionPlayer(Player_t* p);
    void checkCollisionRespawn(Player_t* p);
    bool calcularCollisionDisparo(Disparo* p);
    int checkCollisionKit(Player_t* p);
    int checkCollisionPowerUp(Player_t* p);
    void checkCollisionSpikes(Player_t* p);
    void respawn(int id);
    void respawnEnemy(int id);
    //void bajarHp(int, Player_t*);
    static void movePlayer();
    static void moveDisparo();
    void setHp(int d);
};