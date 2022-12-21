#include "ronda.hpp"

void Ronda::sumarRonda() {
    if(rondas_player < maxrondas) {
        rondas_player++;
    }
}

bool Ronda::ganarPartida() {
    if(rondas_player == maxrondas) {
        return true;
    }
    return false;
}