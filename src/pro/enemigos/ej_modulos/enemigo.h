#pragma once
#include <SFML/Graphics.hpp>


class Enemigo{ 
    protected: 
        int vida;
        int rango;
        sf::Sprite sprite;
        sf::Texture tex;
    public:
        Enemigo();
        sf::Sprite getSprite();
};


class Pincho : public Enemigo{
    public:
        Pincho();
};

class Fantasma : public Enemigo{
    public: 
        Fantasma();
        sf::Sprite getSprite();
};

class Golem : public Enemigo{
    public:
        Golem();
        sf::Sprite getSprite();
};
 
class Minotauro : public Enemigo{
    public: 
        Minotauro();
        sf::Sprite getSprite();
};
