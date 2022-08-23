#pragma once
#include "SFML/Graphics.hpp"
class MenuControles{
    private:    
        sf::Text texto[1];
        sf::Texture textBack;
        sf::Sprite background;
        sf::Font font;
        int itemSelected;

    public:
        MenuControles(int, int);
        int getItemSelected();
        void draw(sf::RenderWindow &);
};