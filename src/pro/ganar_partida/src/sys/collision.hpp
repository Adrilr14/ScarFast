#pragma once

#include <SFML/Graphics.hpp>

class Collision
{
public:
    Collision();
    ~Collision();
    bool collidesWith(sf::Sprite *sp1, sf::Sprite *sp2);

/*private:
    sf::Sprite *sp;
    bool collides;*/
};
