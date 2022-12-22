#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class minotauro{
    

    public:
        minotauro();
        sf::Sprite getSprite();
        void update();
        void movimiento();

    private:
        sf::Sprite sprite;
        sf::Texture tex;


};