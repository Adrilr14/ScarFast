#pragma once
#include <string>
#include "../sys/physics.hpp"
#include "util.hpp"

class Sprite_t {
private:
    int id {-1};     
    int width {0};
    int height {0};
    Physics_t* phy;
    std::string route {""};
    State_v state {State_v::visible};
    bool collisionable {false};
public:
    Sprite_t(){};
    Sprite_t(int i,const std::string& r, int w, int h, bool col) : id(i), route(r), width(w), height(h), collisionable(col) {}; 

    Sprite_t(int i,const std::string& r, int w, int h, bool col, Physics_t* p) : id(i), route(r) , width(w), height(h), collisionable(col), phy(p) {}; 
    ~Sprite_t(){};

    void loadSprites();
    auto getID() { return id; };
    auto getWidth() { return width; };
    auto getHeight() { return height; };
    auto& getRoute() { return route; };
    auto& getPhysics() { return phy; };
    auto getCollisionable() { return collisionable; };
};