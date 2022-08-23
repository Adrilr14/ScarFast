#include "ia.hpp"

// Constructores
IA::IA() : comportamiento(TipoIA::nothing), range(std::pair<float, float>(0.f, 0.f)) {}

IA::IA(std::vector<std::pair<float,float>> p) : comportamiento(TipoIA::patrol), patrol(p){}

IA::IA(std::pair<float, float> r, TipoIA c) : comportamiento(c), range(r) {
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

std::vector<std::pair<float,float>> IA::getPatrol(){
    return patrol;
}

void IA::setPatrol(std::vector<std::pair<float,float>> p){
    patrol = p;
}

std::pair<float, float> IA::getRange() {
    return range;
}

void IA::setRange(std::pair<float, float> r) {
    range = r;
}
