#pragma once
#include <string>
#include "../sys/physics.hpp"

enum State_v {
    visible,
    hidden
};

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
    int width_escalado{0};
    int height_escalado{0};
    int frame_r {0};
    int cantidad_frames;
    bool disparo_water {false};

    Sprite_t(){};
    Sprite_t(int i, const std::string& r, int w, int h, bool col, bool water = false) : id(i), route(r), width(w), height(h), collisionable(col), disparo_water(water){}; 

    Sprite_t(int i,const std::string& r, int w, int h, bool col, Physics_t* p) : id(i), route(r) , width(w), height(h), collisionable(col), phy(p) {}; 

    Sprite_t(const std::string& r, int w, int h, Physics_t* p) : route(r), width(w), height(h), phy(p){}
    ~Sprite_t(){};

    void loadSprites();
    auto getID() { return id; };
    auto getWidth() { return width; };
    auto getHeight() { return height; };
    auto& getRoute() { return route; };
    auto& getPhysics() { return phy; };
    auto getVisible() { return state; };
    bool getCollisionable() { return collisionable; };

    void setRoute(std::string s){
        route = s;
    }

    void setWidth(int w){
        width = w;
    }

    void setHeight(int h){
        height = h;
    }

    void setVisible(State_v s){
        state = s;
    }
};