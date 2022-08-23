#pragma once

#include <map>
#include <vector>
#include "../../game/factory/util.hpp"

class Direction_t {
public:
    int dir {-1};
    int dirPrevia {-1};
    std::vector<int> dirCollision;
    std::map<int,Vector2D> valuesDirection {
        {1, Vector2D{ 1  ,  0 ,  90  }    }, //Derecha D || Flecha Right
        {2, Vector2D{-1  ,  0 , -90  }    }, //Izquierda A || Flecha Izq
        {3, Vector2D{ 0  , -1 ,   0  }    }, //Arriba W || Flecha Up *** Abajo S || Flecha Abajo (Es al reves por sfml)
        {4, Vector2D{ 0  ,  1 , 180  }    }, //Abajo S || Flecha Abajo *** Arriba W || Flecha Up
        {5, Vector2D{ 1  , -1 ,  30  }    }, // D && W
        {6, Vector2D{-1  , -1 , -30  }    }, // A && W
        {7, Vector2D{ 1  ,  1 , 150  }    }, // D && S
        {8, Vector2D{-1  ,  1 , -150 }    },  //A && S
    };

    int dirAn {0};
    std::map<int,int> direccionAnimacion{
        { 0,  1 }, //derecha
        { 1, -1 } //izquierda
    };
    
    Direction_t(){};
    ~Direction_t(){};
    Vector2D getValuesDirection(int direccion){
        return valuesDirection[direccion];
    }

    int getDireccionByValues(int x, int y) {
        for(unsigned int i = 0; i < valuesDirection.size(); i++) {
            if(valuesDirection[i+1].m_x == x && valuesDirection[i+1].m_y == y) {
                return i+1;
            }
        }
        return 0;
    }

    std::map<int,int> getDireccionAnimacion() {
        return direccionAnimacion;
    }

    void setDir(int dir) {
        this->dir = dir;
    }

    void setDirPrevia(int dir){
        this->dirPrevia = dir;
    }
};