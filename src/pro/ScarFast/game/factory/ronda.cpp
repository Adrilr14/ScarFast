#include "ronda.hpp"
#include "../Game.hpp"

void Ronda_t::sumarRonda(int i) {

    auto* mapa = Game_t::getInstance()->getMap();
    auto* p_one = Game_t::getInstance()->getPlayerOne();
    auto* p_two = Game_t::getInstance()->getPlayerTwo();
    p_one->getSprite()->getPhysics()->respawn(p_one->getID()); // Restauramos el Player 1 al inicio
    p_two->getSprite()->getPhysics()->respawn(p_two->getID()); // Restauramos el Player 2 al inicio
    puntuaje[i]++;
    // Restauramos los enemigos al inicio
    auto enemigos = Game_t::getInstance()->getEnemies();
    for(unsigned int i = 0; i < enemigos.size(); i++) 
    {
        enemigos[i]->setTimeRespawn(0.f);
        enemigos[i]->getSprite()->getPhysics()->respawnEnemy(enemigos[i]->getID());
    }
    
    mapa->getKit()->getPhysics()->x = mapa->getKitOrigin().first;
    mapa->getKit()->getPhysics()->y = mapa->getKitOrigin().second;
}

int Ronda_t::tryGanarPartida() {
    if(puntuaje[0] == maxr){
        return 0;
    }else if(puntuaje[1] == maxr){
        return 1;
    }
    return -1;
}

void Ronda_t::resetPuntuaje() {
    puntuaje[0] = 0;
    puntuaje[1] = 0;
}

int Ronda_t::getPunuaje(int pos) {
    return puntuaje[pos];
}