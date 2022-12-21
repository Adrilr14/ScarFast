#pragma once
#include "../game/factory/util.hpp"

class Map_t;
class Direction_t;
struct Keyboard_t;

struct Controller_t {
    
    virtual ~Controller_t() = default;
    virtual void createWindow(int width, int height) = 0;
    virtual bool isWindowOpen() = 0;
    virtual void setEnviroment() = 0;
    virtual void checkControlls(Keyboard_t*, Direction_t*) = 0;
    virtual void run() = 0;
    virtual void load_MapSfml(Map_t& p) = 0;
    virtual std::tuple<int,int> getPositionPlayerone() = 0;
    virtual std::tuple<int,int> getPositionSprite(int x, int y) = 0;
    virtual bool load_Sprites(Entity_ID id, std::string v) = 0;
};
