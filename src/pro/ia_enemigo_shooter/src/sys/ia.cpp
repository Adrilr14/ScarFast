#include "ia.hpp"

// Constructores
IA::IA() : comportamiento(TipoIA::nothing) {}

IA::IA(std::vector<sf::Vector2f> p) : comportamiento(TipoIA::patrol), patrol(p){}

IA::IA(sf::RectangleShape *r, TipoIA c) : comportamiento(c), range(r) {
    if(comportamiento != TipoIA::pursuit && comportamiento != TipoIA::shooter)
    {
      comportamiento = TipoIA::pursuit;  
    } 
}

//Destructor
IA::~IA() {}

int IA::getTipoIA(){
    return comportamiento;
}

std::vector<sf::Vector2f> IA::getPatrol(){
    return patrol;
}

void IA::setPatrol(std::vector<sf::Vector2f> p){
    patrol = p;
}

sf::RectangleShape* IA::getRange() {
    return range;
}

void IA::setRange(sf::RectangleShape *r) {
    range = r;
}
