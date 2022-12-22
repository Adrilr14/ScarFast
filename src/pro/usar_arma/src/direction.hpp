#pragma once

#include <map>
#include "util.hpp"

class Direction_t {
public:
    int dir {-1};
    int dirPrevia {-1};
    int dirCollision {-1};
    std::map<int,Vector2D> valuesDirection {
        {1, Vector2D{ 1  ,  0 ,  90  }    }, //Derecha D || Flecha Right
        {2, Vector2D{-1  ,  0 , -90  }    }, //Izquierda A || Flecha Izq
        {3, Vector2D{ 0  ,  1 ,   0  }    }, //Arriba W || Flecha Up
        {4, Vector2D{ 0  , -1 , 180  }    }, //Abajo S || Flecha Abajo
        {5, Vector2D{ 1  ,  1 ,  30  }    }, // D && W
        {6, Vector2D{-1  ,  1 , -30  }    }, // A && W
        {7, Vector2D{ 1  , -1 , 150  }    }, // D && S
        {8, Vector2D{-1  , -1 , -150 }    },  //A && S
    };

    Direction_t(){};
    ~Direction_t(){};
    Vector2D getValuesDirection(int direccion){
        return valuesDirection[direccion];
    }
};