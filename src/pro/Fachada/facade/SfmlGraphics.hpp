#pragma once

#include "Controller.hpp"
#include <SFML/Graphics.hpp>

struct SfmlGraphics : public Controller_t {

private:
    sf::RenderWindow *window;

public:
    SfmlGraphics(){};
    virtual ~SfmlGraphics(){};
    void createWindow() override;
    void run() override;
    bool load_Sprites(std::string v) override;
};
