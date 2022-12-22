#pragma once
#include "SFML/Graphics.hpp"

#define Max_items 4

class MenuP
{
private:
    int itemSelected;
    sf::Text texto[Max_items];
    sf::Font font;

public:
    MenuP(float width, float height, int itemSelected, sf::Font font);
    ~MenuP();

    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetItemSelected();
};

