#pragma once
#include "SFML/Graphics.hpp"
#include "../game/factory/MainSound.h"

#define Max_items 5

class Menu
{
private:
    int itemSelected;
    sf::Text texto[Max_items];
    sf::Font font;
    MainSound* sounds;
    sf::Sprite background;
    sf::Texture textBack;

public:
    Menu(float width, float height, int itemSelected);
    ~Menu();

    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetItemSelected();
    MainSound* getSound();
};