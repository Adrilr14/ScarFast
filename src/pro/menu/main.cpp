#include <SFML/Graphics.hpp>
#include <iostream>
#include "src/menu.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(600,600),"SFML works!");

    sf::Font font;
    font.loadFromFile("fonts/arial/arial.ttf");

    Menu menu(window.getSize().x, window.getSize().y, 0, font);

    while(window.isOpen()){

        sf::Event event;

        while(window.pollEvent(event)){

            switch(event.type){
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    menu.MoveUp();
                    break;
                
                case sf::Keyboard::Down:
                    menu.MoveDown();
                    break;
                
                case sf::Keyboard::Return:
                    switch (menu.GetItemSelected()){
                    
                    case 0:
                        std::cout<<"Jugar se ha presionado" << std::endl;
                        break;
                    
                    case 1:
                        std::cout<<"Opciones se ha presionado" << std::endl;
                        break;
                    
                    case 2:
                        window.close();
                        break;
                    }
                    break;
                }
                break;

            case sf::Event::Closed:
                window.close();
                break;
            }

        }
        window.clear();
        menu.draw(window);
        window.display();
    }

    return 0;
}

