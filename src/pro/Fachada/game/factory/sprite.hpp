#pragma once
#include <string>
#include "util.hpp"

class Sprite_t {
private:
    std::string route {""};
    State_v state {State_v::visible};
public:
    Sprite_t(std::string& r) : route(r) {};
    void loadSprites(std::string v);
    ~Sprite_t();
};