#include "player.hpp"

#include <cmath>
#include "map.hpp"
#include "../../facade/ControllerMan.hpp"
#include "../../facade/Controller.hpp"

void Player::checkKeyboard() {
    
        //Jugador 1
        keyboard->button_W   = false;
        keyboard->button_A   = false;
        keyboard->button_S   = false;
        keyboard->button_D   = false;

    
        keyboard->button_Down= false;
        keyboard->button_Up  = false;
        keyboard->button_Left= false;
        keyboard->button_Right = false;
    
    ControllerMan::instancia().controller().checkControlls(this->keyboard,this->direc);
}


bool Collision(int playerx, int playery, int widthplayer, int heightplayer, int posOjbx, int posObjy, int widthObj, int heightObj){

        std::cout << "Player: " << playerx << " " << playery << " " << widthplayer << " " << heightplayer << std::endl;
        std::cout << "Obj: " << posOjbx << " " << posObjy << " " << widthObj << " " << heightObj << std::endl;
        //
        auto fMinx = playerx - (widthplayer/2);
        auto fMaxx = playerx + (widthplayer/2);

        auto sMinx = posOjbx - (widthObj/2);
        auto sMaxx = posOjbx + (widthObj/2);

        //Ahora hacemos un if comprobando si colisionan en x; Si colisiona seguimos comprobando
        //Si no paramos porque para que vamos a seguir haciendo calculos innecesarios

        if(fMinx <= sMaxx && fMaxx >= sMinx){

            //Ejes en Y
            auto fMiny = playery - (heightplayer/2);
            auto fMaxy = playery + (heightplayer/2);

            auto sMiny = posObjy - (heightObj/2);
            auto sMaxy = posObjy + (heightObj/2);

            if(fMiny <= sMaxy && fMaxy >= sMiny){
                std::cout << "Colisiona" << std::endl;
                return true;
            }
        }
        return false;
    }



void Player::getCuadrante(Map_t& mapa) {
    auto x = std::get<0>(phy.getPosition());
    auto y = std::get<1>(phy.getPosition());

    auto cuadranteX = round(x / TILES_WIDTH);
    auto cuadranteY = round(y / TILES_HEIGHT); 

    auto posPlayer = ControllerMan::instancia().controller().getPositionPlayerone();
    
    if(cuadranteX > 0 && cuadranteY > 0 && cuadranteY < mapa.getMatrizMapa().size() && cuadranteX < mapa.getMatrizMapa()[0].size()){
        //Esta dentro del mapa
        //!!!!Controlar que no se salga del mapa
        auto around = phy.calcularCuadrante(cuadranteX,cuadranteY);
        
        bool comprobar = false;

        for(int i = 0; i < around.size(); i++) {
            auto& spr = mapa.getMatrizMapa()[around[i].second][around[i].first];
            if(spr->getID() != 9){
                //Objeto
            
                auto widthObj = spr->getWidth();
                auto heighthObj = spr->getHeight();
                auto xObj = spr->getPhysics()->x;
                auto yObj = spr->getPhysics()->y;

                //Player
                auto widthPlayer = 20;
                auto heightPlayer = 20;
                auto posPlayer = ControllerMan::instancia().controller().getPositionPlayerone();
                auto posx = std::get<0>(posPlayer);
                auto posy = std::get<1>(posPlayer);

                bool col = Collision(posx,posy,widthPlayer,heightPlayer,xObj-10,yObj-15,widthObj,heighthObj);
                
                if(col){   
                    
                    comprobar = true;
                    for (const auto& n : direc->valuesDirection) {
                        if(n.second.m_x == (around[i].first - cuadranteX) && n.second.m_z == ( -1*(around[i].second-cuadranteY))){
                            direc->dirCollision.push_back(n.first);
                        }
                    }
                    
                    //direc->dirCollision = direc->dirPrevia;
                    //std::cout << "Colisiona" << std::endl;
                }else{
                    if(!comprobar){
                        direc->dirCollision.clear();
                        direc->dirCollision.push_back(-1);
                    }
                }
            }
        }
    }
}