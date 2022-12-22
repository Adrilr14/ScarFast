#include "collision.h"

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
