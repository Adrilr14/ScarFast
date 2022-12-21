#include "MenuControles.hpp"
#include <SFML/Graphics.hpp>

MenuControles::MenuControles(int width, int height){
    itemSelected = 0;
    if(!textBack.loadFromFile("resources/controles.jpg")){
        exit(0);
    }

    font.loadFromFile("resources/fonts/fuente.ttf");

    background.setTexture(textBack);
    background.setTextureRect(sf::IntRect(0,0, (int)width, (int)height));

    texto[0].setFont(font);
    texto[0].setString("Atras");
    texto[0].setCharacterSize(50);
    texto[0].setColor(sf::Color::Yellow);
    texto[0].setPosition(sf::Vector2f(width / 2 - (50*30)/2, height / (5 + 1)* 4)); 
}

void MenuControles::draw(sf::RenderWindow &window){
    window.draw(background);
    for (size_t i = 0; i < 1; i++)
    {
        window.draw(texto[i]);
    }
}

int MenuControles::getItemSelected(){
    return itemSelected;
}