#pragma once
#include "util.hpp"
#include "sprite.hpp"
#include "../sys/time.hpp"

#define INCREMENT_SPEED 60
#define SHIELD          40

enum Category_t {       //Porcentajes
    increase_speed,     // 30%
    spikes,             // 60%
    shield,             // 70%
    decrease_speed,     // 30%
    invunerabilty       // 5%
};


class Power_Up {

private:
    EntityID_t entityID { ++nextID };
	inline static EntityID_t nextID {0};
    Sprite_t* spr;      //Sprite por defecto que siempre es la caja sorpresa
    int tiempo_box;     //Duracion que tiene la caja en el mapa
    int tiempo_item;    //Duracion que tiene el powerUp
    Category_t type;    //Tipo que se le asigna a la caja random
    bool activate {false}; //Este booleano sirve para saber cual se ha elegido del array
    bool used {false};
    Temporizador_t* temporizador {nullptr};
    inline static int examinar = 0;
public:

    Power_Up(Sprite_t* s, int t_b = 10 , int t_i = 5) : 
    spr(s), tiempo_box(t_b), tiempo_item(t_i){};

    static void create_powerUp_for_the_map();
    static void reset_activate_values();
    void use_power_up(Player_t*);
    void disabled_PowerUp(Player_t* p);

    auto  getID()           { return entityID;}
    auto& getSprite()       { return spr; }
    auto  getTiempo_box()   { return tiempo_box; }
    auto  getTiempo_item()  { return tiempo_item; }
    auto  getCategory()     { return type; }
    auto  getActivate()     { return activate; }
    auto  getUsed()         { return used;}
    auto& getTemporizador() { return temporizador;}

    void  setActivate(bool a)       { activate = a; }
    void  setCategory(Category_t t) { type = t; }
    void  setUsed(bool u)           { used = u; }
    static void setExaminar(int i)   { examinar = i;}
};