#pragma once
#include "util.hpp"
#include "../sys/physics.hpp"
#include "../sys/hp.hpp"
#include "../sys/direction.hpp"
#include "sprite.hpp"
#include "arma.hpp"
#include "MainSound.h"
#include "map.hpp"

#define ID_PLAYER_ONE 1
#define ID_PLAYER_TWO 2

class Power_Up;

class Player_t {
private:
    EntityID_t entityID { ++nextID };
	inline static EntityID_t nextID {0};
    Hp_t* hp;
    Direction_t* direccion;
    Sprite_t* spr;
    Arma* arma {nullptr};
    Disparo* disparo {nullptr};
    Sprite_t* kit {nullptr};
    Power_Up* powerUp {nullptr};
    Personajes pers{Personajes::minotauro};
    Estado_Personaje estado {Estado_Personaje::parado};
    MainSound* sounds;

    // Variables auxiliares
    bool invulnerable {false};
    bool receive_damage{false};
    std::tuple<int,int,int,int> nextColor {std::tuple<int,int,int,int>(255,19,21,255)};
    float timeRecover {0.f};
    float timeAnimation {0.f};
    double tiempo_transcurrido {0.0};
    float timeKit {0.f};
public:
    Player_t(const char* route, int width, int height, Arma* arma);
    ~Player_t();

    void checkCollisions();
    void powerUpUsed();

    //Getters y setters
    Sprite_t* getSprite();
    Direction_t* getDireccion();
    EntityID_t getID();
    Sprite_t* getKit();
    Power_Up* getPowerUp();
    Hp_t* getHp();
    void setHp(Hp_t* vida);
    Personajes getPersonaje();
    void setPersonaje(Personajes pers);
    Estado_Personaje getEstado();
    bool getInvulnerable();
    bool getReceive_damage();
    MainSound* getSonido();

    Arma* getArma();
    Disparo* getDisparo();
    void setArma(Arma* a);
    void setDisparo(Disparo* d);
    void setKit(Sprite_t* k);
    void setPowerUp(Power_Up* pw);
    void setEstado(Estado_Personaje s);
    void setInvulnerable(bool v);
    void setReceive_damage(bool receive_damage);
    void setEstado_after_dead(Estado_Personaje s);

    float getTimeAnimation();
    void updateTimeAnimation();
    void setTimeAnimation(float newTime);

    float getTimeKit();
    void updateTimeKit();
    void setTimeKit(float newTime);
};