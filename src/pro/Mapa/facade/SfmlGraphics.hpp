#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <tuple>

#include "Controller.hpp"
//#include "tinyxml2.h"
#include "../game/factory/util.hpp"
#include "../game/factory/map.hpp"
#include "../game/factory/keyboard.hpp"

class Direction_t;

struct SfmlGraphics : public Controller_t {

private:
    sf::RenderWindow *window;
    std::vector<std::vector<sf::Sprite*>> sprites;
    std::vector<sf::Sprite*> solidos;
    std::vector<sf::Texture*> texturesMap;
    sf::Texture* tex;
    sf::Texture tex2;
    sf::Sprite* sprite;
    sf::Sprite sprite2;
    sf::Vector2f oldPosSp;
    Map_t map;
public:
    SfmlGraphics(){};
    virtual ~SfmlGraphics(){};
    void createWindow(int width, int height) override;
    bool isWindowOpen() override;
    void setEnviroment() override;
    void checkControlls(Keyboard_t* k, Direction_t* t) override;
    void run() override;
    void load_MapSfml(Map_t& p) override;
    bool load_Sprites(Entity_ID id, std::string v) override;
    std::tuple<int,int> getPositionPlayerone() override;
    std::tuple<int,int> getPositionSprite(int x, int y);
    bool checkCollisions(sf::Sprite *sp1, sf::Sprite *sp2);
};
