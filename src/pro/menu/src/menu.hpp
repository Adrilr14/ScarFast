#pragma once
#include "SFML/Graphics.hpp"

#define Max_items 5

class Menu
{
private:
    int itemSelected;
    sf::Text texto[Max_items];
    sf::Font font;

public:
    Menu(float width, float height, int itemSelected, sf::Font font);
    ~Menu();

    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetItemSelected();
};

