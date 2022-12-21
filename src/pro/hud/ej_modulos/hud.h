#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Hud{
    private:
        int vida;
        sf::Texture textura;
        sf::Texture textArma;
        sf::Sprite corLleno;
        sf::Sprite corMedio;
        sf::Sprite arma;
    public:
        Hud();
        void dibujarCorazon(sf::RenderWindow &);
        void bajarVida(int);
        void pintarObjeto(int, sf::RenderWindow &);
};