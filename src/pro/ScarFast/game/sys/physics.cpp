#include "physics.hpp"
#include "../../Game.hpp"
#include "../factory/disparo.hpp"
#include "../../facade/ControllerMan.hpp"
#include <math.h>
#include <iostream>


bool checkDirCollision(Player_t* p){
    for(unsigned int i = 0; i < p->getDireccion()->dirCollision.size();i++){
        if(p->getDireccion()->dirCollision[i] == p->getDireccion()->dir){
            return true;
        }
    }
    return false;
}

bool Collision(std::tuple<double,double,int,int> one, std::tuple<double,double,int,int> two){
    
    auto fMinx = std::get<0>(one) - (std::get<2>(one)/2);
    auto fMaxx = std::get<0>(one) + (std::get<2>(one)/2);

    auto sMinx = std::get<0>(two) - (std::get<2>(two)/2);
    auto sMaxx = std::get<0>(two) + (std::get<2>(two)/2);

    auto fMiny = std::get<1>(one) - (std::get<3>(one)/2);
    auto fMaxy = std::get<1>(one) + (std::get<3>(one)/2);

    auto sMiny = std::get<1>(two) - (std::get<3>(two)/2);
    auto sMaxy = std::get<1>(two) + (std::get<3>(two)/2);

    if(fMinx <= sMaxx && fMaxx >= sMinx && fMiny <= sMaxy && fMaxy >= sMiny){
        return true;
    }
    return false;
}

std::tuple<int,int> Physics_t::getPosition(Player_t* p) {
    return std::make_tuple<int,int>(p->getSprite()->getPhysics()->x,
                                    p->getSprite()->getPhysics()->y);
}

void Physics_t::calcularCollisionPlayer(Player_t* p) {
    auto& mapa = *Game_t::getInstance()->getMap();

   auto cuadranteX = ((int)(p->getSprite()->getPhysics()->x + p->getSprite()->getWidth()/2)  / TILES_WIDTH)-1;
   auto cuadranteY = ((int)(p->getSprite()->getPhysics()->y + p->getSprite()->getHeight()/2) / TILES_HEIGHT);

    p->getDireccion()->dirCollision.clear();

   if(cuadranteX >= 0 && cuadranteY >= 0 && cuadranteY < mapa.getMatrizMapa().size() && cuadranteX < mapa.getMatrizMapa()[0].size()) {
       for(unsigned int i = 0; i < p->getDireccion()->valuesDirection.size(); i++){
           auto* spr = mapa.getMatrizMapa()[cuadranteY+p->getDireccion()->valuesDirection[i].m_y][cuadranteX+p->getDireccion()->valuesDirection[i].m_x];
           if(spr != nullptr && spr->getCollisionable()) {
               bool colision =  Collision(std::tuple<double,double,int,int>(p->getSprite()->getPhysics()->x+5,p->getSprite()->getPhysics()->y+10,p->getSprite()->getWidth(), p->getSprite()->getHeight()),std::tuple<double,double,int,int>(spr->getPhysics()->x,spr->getPhysics()->y, spr->getWidth(), spr->getHeight()));
               if(colision) {
                   int direccion = p->getDireccion()->getDireccionByValues(p->getDireccion()->valuesDirection[i].m_x, p->getDireccion()->valuesDirection[i].m_y);
                   p->getDireccion()->dirCollision.push_back(direccion);
               }
           }
       }
   }
}

bool Physics_t::calcularCollisionDisparo(Disparo* disparo) {
    auto& mapa = *Game_t::getInstance()->getMap();
    auto cuadranteX = round( ((disparo->getSprite()->getPhysics()->x) + (disparo->getSprite()->getWidth()/2)) / TILES_WIDTH)-1;   
    auto cuadranteY = round( ((disparo->getSprite()->getPhysics()->y) + (disparo->getSprite()->getHeight()/2)) / TILES_HEIGHT)-1;

    for(unsigned int i = 0; i < cuadrante.size(); i++) {
        if(cuadranteX > 0 && cuadranteY > 0 && cuadranteY+cuadrante[i].second < mapa.getHeightMap() && cuadranteX+cuadrante[i].first < mapa.getWithMap()){
        auto* spr = mapa.getMatrizMapa()[cuadranteY+cuadrante[i].second][cuadranteX+cuadrante[i].first];
            if(spr != nullptr && spr->getCollisionable() != false && spr->disparo_water == false){
                /*bool colision = ControllerMan::instancia().controller().checkCollisionDisparo(
                    cuadranteY+cuadrante[i].second, 
                    cuadranteX+cuadrante[i].first,
                    disparo->getID());
                return colision;*/
                return true;
            }
        }
            return ControllerMan::instancia().controller().checkCollisionDisparoPlayerAndEnemy(disparo->getID());
        }
    return false;
}

int Physics_t::checkCollisionKit(Player_t* p) {
    int res = 0;
    //Conseguimos los dos jugadores para checkear si colisionan 
    auto* p_spr = p->getSprite();
    auto& kit = *Game_t::getInstance()->getMap()->getKit();
    bool colision = ControllerMan::instancia().controller().checkCollisionKit(p->getID());

    if(colision && kit.getVisible() == State_v::visible && ControllerMan::instancia().controller().getTimeElapsed() >= p->getTimeKit()) {
        //Comprobamos si ha colisionado con el personaje 1 el Kit.
        p->getSonido()->play("pack");
        kit.setVisible(State_v::hidden);
        p->setKit(&kit);
        res=1;
    }
    return res;
}

void Physics_t::checkCollisionRespawn(Player_t* p) {
    Hud* hud = Game_t::getInstance()->getHud();
    auto* p_one = Game_t::getInstance()->getPlayerOne();
    auto* p_two = Game_t::getInstance()->getPlayerTwo();
    bool colision = ControllerMan::instancia().controller().checkCollisionRespawn(p->getID());

    if(colision && p->getKit() != nullptr) {
        //Significa que ha ganado la ronda
        //Quitamos el kit del personaje que lo llevaba

        p->getSonido()->play("ganarRonda");
        auto* mapa = Game_t::getInstance()->getMap();
        p->setKit(nullptr);
        p_two->setPowerUp(nullptr);
        p_one->setPowerUp(nullptr);
        //Le sumamos la ronda
        Game_t::getInstance()->getRonda()->sumarRonda(p->getID()-1);
        //Posicionar a los personajes en su respectivo respawn
       
        //Volvemos a dejar el Sprite del Kit en visible para que se pueda coger
        mapa->getKit()->setVisible(State_v::visible);
        
        Game_t::getInstance()->getPlayerOne()->getSprite()->getPhysics()->x = mapa->getRespawn_one()->getPhysics()->x;
        Game_t::getInstance()->getPlayerOne()->getSprite()->getPhysics()->y = mapa->getRespawn_one()->getPhysics()->y;
        //Game_t::getInstance()->getState()->endScene();
        Game_t::getInstance()->setGameStart(false);
        Temporizador_t* t = new Temporizador_t(SET_UP_FOR_GAME);
        Game_t::getInstance()->setTemporizador(t);

    }
}

int Physics_t::checkCollisionPowerUp(Player_t* p) {
    int res = 0;
    auto& mapa = *Game_t::getInstance()->getMap();

    std::pair<EntityID_t,bool> colision = ControllerMan::instancia().controller().checkCollisionPowerUps(p->getID());

    if(colision.second) {
        for(unsigned int i = 0; i < mapa.getPowerUps().size(); i++) {
            if(mapa.getPowerUps()[i]->getID() == colision.first && p->getPowerUp() == nullptr) {
                p->getSonido()->play("powerup");
                p->setPowerUp(mapa.getPowerUps()[i]);
                res=1;
            }
        }
    }
    return res;
}


void Physics_t::checkCollisionSpikes(Player_t* p) {
    if(p->getID() == ID_PLAYER_ONE){
        if(Game_t::getInstance()->getPlayerTwo()->getPowerUp() != nullptr){
            if( Game_t::getInstance()->getPlayerTwo()->getPowerUp()->getCategory() == Category_t::spikes && 
                Game_t::getInstance()->getPlayerTwo()->getPowerUp()->getUsed() == true){
                //Comprobamos la colision
                bool c = ControllerMan::instancia().controller().checkCollisionSpikes(p->getID());
                if(c && !p->getReceive_damage() && p->getEstado() != Estado_Personaje::morir){
                    //std::cout << "Me hago daño\n";
                    p->getHp()->reduceHp(20);
                    if (p->getHp()->getHp() > 0)
                    {
                        p->setReceive_damage(true);
                    }
                }
            }
        }
    }else{
        if(Game_t::getInstance()->getPlayerOne()->getPowerUp() != nullptr){
            if( Game_t::getInstance()->getPlayerOne()->getPowerUp()->getCategory() == Category_t::spikes && 
                Game_t::getInstance()->getPlayerOne()->getPowerUp()->getUsed() == true){
                //Comprobamos la colision
                bool c = ControllerMan::instancia().controller().checkCollisionSpikes(p->getID() && p->getEstado() != Estado_Personaje::morir);
                if(c && !p->getReceive_damage() && p->getEstado() != Estado_Personaje::morir){
                    //std::cout << "Me hago daño\n";
                    p->getHp()->reduceHp(20);
                    if (p->getHp()->getHp() > 0)
                    {
                        p->setReceive_damage(true);
                    }
                }
            }
        }
    }
}

void Physics_t::respawn(int id) {
    auto* mapa = Game_t::getInstance()->getMap();
    if(id == ID_PLAYER_ONE) 
    {
        auto* p_one = Game_t::getInstance()->getPlayerOne();
        p_one->getSprite()->getPhysics()->x = mapa->getRespawn_one()->getPhysics()->x;
        p_one->getSprite()->getPhysics()->y = mapa->getRespawn_one()->getPhysics()->y;
        p_one->getHp()->revivir(); // Se le restarua la vida al Player 1
    }
    else
    {
        auto* p_two = Game_t::getInstance()->getPlayerTwo();
        p_two->getSprite()->getPhysics()->x = mapa->getRespawn_two()->getPhysics()->x;
        p_two->getSprite()->getPhysics()->y = mapa->getRespawn_two()->getPhysics()->y;
        p_two->getHp()->revivir(); // Se le restarua la vida al Player 2
    }
}

void Physics_t::respawnEnemy(int id) {
    auto enemigos = Game_t::getInstance()->getEnemies();
    if(enemigos[id-1]) {
        enemigos[id-1]->getSprite()->getPhysics()->x = enemigos[id-1]->getPositionInit().first;
        enemigos[id-1]->getSprite()->getPhysics()->y = enemigos[id-1]->getPositionInit().second;
        enemigos[id-1]->getHp()->revivir();
        //enemigos[id-1]->setEstado_after_dead(Estado_Personaje::parado); // SI SE PONE SALE DEL VECTOR DE FRAMES Y DA ERROR CUANDO HAY UN ENEMIGO MUERTO Y SE LLEGA AL RESPAWN CON EL KIT
        if(enemigos[id-1]->getComportamiento()->getTipoIA() == TipoIA::patrol) enemigos[id-1]->setPatrolPosition(0);
    }
}

void Physics_t::movePlayer() {
    Keyboard_t* key = Game_t::getInstance()->getKeyboard();
    auto* p_one = Game_t::getInstance()->getPlayerOne();
    auto* p_two = Game_t::getInstance()->getPlayerTwo();
    auto* mapa = Game_t::getInstance()->getMap();

    bool busca = false;
    auto elapsedtime = ControllerMan::instancia().controller().getDeltaTime();

    if(key->key_W && p_one->getEstado() != Estado_Personaje::morir) {
        p_one->getDireccion()->setDirPrevia(p_one->getDireccion()->dir);
        p_one->getDireccion()->setDir(3);
        busca = checkDirCollision(p_one);

        p_one->getSonido()->play("movimiento");
        

        if(!busca){
            p_one->getSprite()->getPhysics()->y -= p_one->getSprite()->getPhysics()->vely * elapsedtime;
        }
    }
    if(key->key_A && p_one->getEstado() != Estado_Personaje::morir) {
        p_one->getDireccion()->setDirPrevia(p_one->getDireccion()->dir);
        p_one->getDireccion()->setDir(2);
        busca = checkDirCollision(p_one);
        p_one->getSonido()->play("movimiento");
        p_one->getDireccion()->dirAn = 1;
        p_one->setEstado(Estado_Personaje::andar);
        if(!busca){
            p_one->getSprite()->getPhysics()->x -= p_one->getSprite()->getPhysics()->velx * elapsedtime;
        }
    }
    if(key->key_S && p_one->getEstado() != Estado_Personaje::morir) {
        p_one->getDireccion()->setDirPrevia(p_one->getDireccion()->dir);
        p_one->getDireccion()->setDir(4);
        busca = checkDirCollision(p_one);
        p_one->setEstado(Estado_Personaje::andar);
        p_one->getSonido()->play("movimiento");
        p_one->getDireccion()->dirAn = 0;

        if(!busca){
            p_one->getSprite()->getPhysics()->y += p_one->getSprite()->getPhysics()->vely * elapsedtime;
        }
    }
    if(key->key_D && p_one->getEstado() != Estado_Personaje::morir) {
        p_one->getDireccion()->setDirPrevia(p_one->getDireccion()->dir);
        p_one->getDireccion()->setDir(1);
        busca = checkDirCollision(p_one);
        p_one->setEstado(Estado_Personaje::andar);
        p_one->getSonido()->play("movimiento");
        p_one->getDireccion()->dirAn = 0;
        if(!busca){
            p_one->getSprite()->getPhysics()->x += p_one->getSprite()->getPhysics()->velx * elapsedtime;
        }
    }
    if(key->key_Right && p_two->getEstado() != Estado_Personaje::morir) {
        p_two->getDireccion()->setDirPrevia(p_two->getDireccion()->dir);
        p_two->getDireccion()->setDir(1);
        busca = checkDirCollision(p_two);
        p_two->setEstado(Estado_Personaje::andar);
        p_two->getSonido()->play("movimiento");
        p_two->getDireccion()->dirAn = 0;
        if(!busca){
            p_two->getSprite()->getPhysics()->x += p_two->getSprite()->getPhysics()->velx * elapsedtime;
        }
    }
    if(key->key_Down && p_two->getEstado() != Estado_Personaje::morir) {
        p_two->getDireccion()->setDirPrevia(p_two->getDireccion()->dir);
        p_two->getDireccion()->setDir(4);
        busca = checkDirCollision(p_two);

        p_two->getSonido()->play("movimiento");

        if(!busca){
            p_two->getSprite()->getPhysics()->y += p_two->getSprite()->getPhysics()->vely * elapsedtime;
        }
    }
    if(key->key_Left && p_two->getEstado() != Estado_Personaje::morir) {
        p_two->getDireccion()->setDirPrevia(p_two->getDireccion()->dir);
        p_two->getDireccion()->setDir(2);
        busca = checkDirCollision(p_two);
        p_two->getSonido()->play("movimiento");
        p_two->getDireccion()->dirAn = 1;
        p_two->setEstado(Estado_Personaje::andar);

        if(!busca){
            p_two->getSprite()->getPhysics()->x -= p_two->getSprite()->getPhysics()->velx * elapsedtime;
        }
    }
    if(key->key_Up && p_two->getEstado() != Estado_Personaje::morir) {
        p_two->getDireccion()->setDirPrevia(p_two->getDireccion()->dir);
        p_two->getDireccion()->setDir(3);
        busca = checkDirCollision(p_two);
        p_two->getSonido()->play("movimiento");
        p_two->getDireccion()->dirAn = 1;
        p_two->setEstado(Estado_Personaje::andar);

        if(!busca){
            p_two->getSprite()->getPhysics()->y -= p_two->getSprite()->getPhysics()->vely * elapsedtime;
        }
    }
    if(key->key_Space && p_one->getEstado() != Estado_Personaje::morir && p_one->getKit() == nullptr){ //Para las armas
        if(p_one->getArma() && p_one->getArma()->getCargas() > 0 && ControllerMan::instancia().controller().getTimeElapsed() >= p_one->getArma()->getTimeCountdown()){   
            if(p_one->getArma()->getTipoArma() == TipoArma::magia)
            {
                auto* disparo = p_one->getArma()->disparar(p_one);
                Map_Disparos::disparos.insert({disparo->getEntity(),disparo});
                p_one->getArma()->setCargas(p_one->getArma()->getCargas()-1);
                p_one->getArma()->updateTimeCountdown();
            }
            else if(p_one->getArma()->getTipoArma() == TipoArma::espada)
            {
                ControllerMan::instancia().controller().attackmele(p_one);
                Game_t::getInstance()->getPlayerOne()->setEstado(Estado_Personaje::atacar);
                p_one->getArma()->setCargas(p_one->getArma()->getCargas()-1);
                p_one->getArma()->updateTimeCountdown();
            }
        }
    }
    else if(key->key_Space && p_one->getEstado() != Estado_Personaje::morir && p_one->getKit() != nullptr)
    {
        p_one->getKit()->setVisible(State_v::visible);
        p_one->getKit()->getPhysics()->x = p_one->getSprite()->getPhysics()->x;
        p_one->getKit()->getPhysics()->y = p_one->getSprite()->getPhysics()->y;
        p_one->updateTimeKit();
        p_one->setKit(nullptr);
        p_one->getArma()->updateTimeCountdown();
    }
    
    if(key->key_Enter && p_two->getEstado() != Estado_Personaje::morir && p_two->getKit() == nullptr){ //Para las armas
        if(p_two->getArma() && p_two->getArma()->getCargas() > 0 && ControllerMan::instancia().controller().getTimeElapsed() >= p_two->getArma()->getTimeCountdown()){   
            if(p_two->getArma()->getTipoArma() == TipoArma::magia)
            {
                auto* disparo = p_two->getArma()->disparar(p_two);
                Map_Disparos::disparos.insert({disparo->getEntity(),disparo});
                p_two->getArma()->setCargas(p_two->getArma()->getCargas()-1);
                p_two->getArma()->updateTimeCountdown();
            }
            else if(p_two->getArma()->getTipoArma() == TipoArma::espada)
            {
                ControllerMan::instancia().controller().attackmele(p_two);
                Game_t::getInstance()->getPlayerTwo()->setEstado(Estado_Personaje::atacar);
                p_two->getArma()->setCargas(p_two->getArma()->getCargas()-1);
                p_two->getArma()->updateTimeCountdown();
            }
        }
    }
    else if(key->key_Enter && p_two->getEstado() != Estado_Personaje::morir && p_two->getKit() != nullptr)
    {
        p_two->getKit()->setVisible(State_v::visible);
        p_two->getKit()->getPhysics()->x = p_two->getSprite()->getPhysics()->x;
        p_two->getKit()->getPhysics()->y = p_two->getSprite()->getPhysics()->y;
        p_two->updateTimeKit();
        p_two->setKit(nullptr);
        p_two->getArma()->updateTimeCountdown();
    }

    if(key->key_shift_left && p_one->getEstado() != Estado_Personaje::morir) { //Para el personaje 1 para powerup
        if(p_one->getPowerUp() != nullptr) {
            if(!p_one->getPowerUp()->getUsed()) {
                p_one->getPowerUp()->use_power_up(p_one);
                p_one->getPowerUp()->setUsed(true);
            }
        }
    }
    if(key->key_shift_right && p_two->getEstado() != Estado_Personaje::morir) { //Para el personaje 2 para powerup
        if(p_two->getPowerUp() != nullptr) {
            if(!p_two->getPowerUp()->getUsed()) {
                p_two->getPowerUp()->use_power_up(p_two);
                p_two->getPowerUp()->setUsed(true);
            }
        }
    }

    if(p_one->getEstado() == Estado_Personaje::andar && !key->key_W && !key->key_A && !key->key_S && !key->key_D && !key->key_Space){
        p_one->setEstado(Estado_Personaje::parado);
    }
    if(p_two->getEstado() == Estado_Personaje::andar && !key->key_Up && !key->key_Down && !key->key_Right && !key->key_Left && !key->key_Enter){
        p_two->setEstado(Estado_Personaje::parado);
    }

    // Animaciones jugadores
    ControllerMan::instancia().controller().revertAnimation(p_one);
    ControllerMan::instancia().controller().animate_frame(p_one->getSprite(),p_one->getID());

    ControllerMan::instancia().controller().revertAnimation(p_two);
    ControllerMan::instancia().controller().animate_frame(p_two->getSprite(),p_two->getID());
}

// Movimiento disparo
void Physics_t::moveDisparo() {
    for(auto& disparos : Map_Disparos::disparos) {
        if(disparos.second != nullptr){
            disparos.second->mover();
        }
    }
}
