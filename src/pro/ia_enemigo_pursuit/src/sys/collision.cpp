#include "collision.hpp"

//Constructor
Collision::Collision() {}

//Destructor
Collision::~Collision() {}

//Funcion para comprobar que dos elementos colisionan
bool Collision::collidesWith(sf::Sprite *sp1, sf::Sprite *sp2)
{
    bool colisiona = false;
    if (sp1->getGlobalBounds().intersects(sp2->getGlobalBounds()))
    {
        colisiona = true;
    }
     return colisiona;
}

//Funcion para comprobar que el jugador colisiona con el rango del enemigo
bool Collision::collidesWithRange(sf::Sprite *sp1, sf::RectangleShape *rect)
{
    bool colisiona = false;
    if (sp1->getGlobalBounds().intersects(rect->getGlobalBounds()))
    {
        colisiona = true;
    }
     return colisiona;
}