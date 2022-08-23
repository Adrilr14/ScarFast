#include "Menu.hpp"

Menu::Menu(float width, float height, int item) : itemSelected(item){

    if(!textBack.loadFromFile("resources/portada.jpg")){
        exit (0);
    }

    background.setTexture(textBack);
    background.setTextureRect(sf::IntRect(0,0, (int)width, (int)height));


    sounds = new MainSound();
    sounds->activarLongSound("intro", ("resources/sounds/Intro.wav"), 30);
    sounds->activarShortSound("click", (new Buffer("resources/sounds/click.wav")), 60);

    font.loadFromFile("resources/fonts/fuente.ttf");

    texto[0].setFont(font);
    texto[0].setString("Jugar");
    texto[0].setCharacterSize(50);
    texto[0].setColor(sf::Color::Yellow);
    texto[0].setPosition(sf::Vector2f(width / 2 - (50*5)/2, height / (Max_items + 1)* 2)); 

    texto[1].setFont(font);
    texto[1].setString("Controles");
    texto[1].setCharacterSize(50);
    texto[1].setColor(sf::Color::White);
    texto[1].setPosition(sf::Vector2f(width / 2 - (50*8)/2, height / (Max_items + 1)* 3)); 

    texto[2].setFont(font);
    texto[2].setString("Salir");
    texto[2].setCharacterSize(50);
    texto[2].setColor(sf::Color::White);
    texto[2].setPosition(sf::Vector2f(width / 2- (50*5)/2, height / (Max_items + 1)* 4)); 

    itemSelected = 0;
}

MainSound* Menu::getSound(){
    return sounds;
}

Menu::~Menu(){}

void Menu::draw(sf::RenderWindow &window){
    window.draw(background);
    for (size_t i = 0; i < Max_items; i++)
    {
        window.draw(texto[i]);
    }
}

void Menu::MoveUp(){

    if(itemSelected - 1 >= 0){
        texto[itemSelected].setColor(sf::Color::White);
        itemSelected--;
        texto[itemSelected].setColor(sf::Color::Yellow);
    }
}

void Menu::MoveDown(){

    if(itemSelected - 1 < Max_items){
        texto[itemSelected].setColor(sf::Color::White);
        itemSelected++;
        texto[itemSelected].setColor(sf::Color::Yellow);
    }
}

int Menu::GetItemSelected(){
    return itemSelected;
}