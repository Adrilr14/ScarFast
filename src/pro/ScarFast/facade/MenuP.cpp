#include "MenuP.hpp"

MenuP::MenuP(float width, float height, int item) : itemSelected(item){


    font.loadFromFile("resources/fonts/arial/arial.ttf");

    texto[0].setFont(font);
    texto[0].setString("Reanudar");
    texto[0].setCharacterSize(50);
    texto[0].setColor(sf::Color::Cyan);
    texto[0].setPosition(sf::Vector2f(width / 2, height / (Max_items + 1)* 1)); 

    texto[1].setFont(font);
    texto[1].setString("Opciones");
    texto[0].setCharacterSize(50);
    texto[1].setColor(sf::Color::White);
    texto[1].setPosition(sf::Vector2f(width / 2, height / (Max_items + 1)* 2)); 

    texto[2].setFont(font);
    texto[2].setString("Cotroles");
    texto[0].setCharacterSize(50);
    texto[2].setColor(sf::Color::White);
    texto[2].setPosition(sf::Vector2f(width / 2, height / (Max_items + 1)* 3)); 

    texto[3].setFont(font);
    texto[3].setString("Opciones");
    texto[0].setCharacterSize(50);
    texto[3].setColor(sf::Color::White);
    texto[3].setPosition(sf::Vector2f(width / 2, height / (Max_items + 1)* 4)); 

    itemSelected = 0;
}
MenuP::~MenuP(){}

void MenuP::draw(sf::RenderWindow &window){

    for (size_t i = 0; i < Max_items; i++)
    {
        window.draw(texto[i]);
    }
}

void MenuP::MoveUp(){

    if(itemSelected - 1 >= 0){
        texto[itemSelected].setColor(sf::Color::White);
        itemSelected--;
        texto[itemSelected].setColor(sf::Color::Cyan);
    }
}

void MenuP::MoveDown(){

    if(itemSelected - 1 < Max_items){
        texto[itemSelected].setColor(sf::Color::White);
        itemSelected++;
        texto[itemSelected].setColor(sf::Color::Cyan);
    }
}

int MenuP::GetItemSelected(){
    return itemSelected;
}