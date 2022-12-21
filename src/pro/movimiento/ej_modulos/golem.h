#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class golem{
    

    public:
        golem();
        sf::Sprite getSprite();
        void update();
        void movimiento();

    private:
        sf::Sprite sprite;
        sf::Texture tex;


};