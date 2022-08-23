#pragma once
#include "../game/factory/MainSound.h"
#include "SFML/Graphics.hpp"

#define Max_items 6

class MenuJugar{
    private:
        bool estado = true;
        int itemSelected;
        int mueveFila = 0;
        sf::Text texto[Max_items][2];
        sf::Font font;
        MainSound* sounds;
        sf::Sprite background;
        sf::Texture textBack;
        sf::Sprite golem;
        sf::Sprite mino;
        sf::Texture textGol;
        sf::Texture textMino;
        sf::Sprite botonIzq[3];
        sf::Sprite botonDer[3];
        sf::Texture textDer;
        sf::Texture textIzq;
        sf::Texture tJug1; 
        sf::Texture tJug2;
        sf::Sprite jug1;
        sf::Sprite jug2;
        inline static int mapa;
        inline static int jugador1 {1};
        inline static int jugador2 {0};
        
    public:
        MenuJugar(int, int, int);
        void drawBackground(sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);
        void MoveUp();
        void MoveDown();
        int GetItemSelected();
        void move(int);
        MainSound* getSound();
        void cambiarSprite(int, int);
        void elegirMapa(int);

        //getters y setters
        static int getMapa();
        void setMapa(int mapa);

        static int getJugador1();
        void setJugador1(int jugador1);

        static int getJugador2();
        void setJugador2(int jugador2);
};