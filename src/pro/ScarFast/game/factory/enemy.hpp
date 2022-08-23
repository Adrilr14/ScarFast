#pragma once

#include <iostream>
#include <tuple>
#include "util.hpp"
#include "../sys/hp.hpp"

class IA;
class Player_t;
class Disparo;
class Sprite_t;

class Enemy{

private:
    EntityID_t entityID { ++nextID };
	inline static EntityID_t nextID {0};
    Hp_t* hp;
    int damage;
    Sprite_t *spEnemy;
    IA *comportamiento;
    int patrolPosition {0};
    int tipoMagia;
    float cadenciaDisparo;
    std::pair<float,float> posInicial;
    Personajes enemy{Personajes::enemigo1};
    Estado_Personaje estado {Estado_Personaje::parado};

    // Variables auxiliares
    float timeReload {0.f};
    bool receive_damage {false};
    std::tuple<int,int,int,int> nextColor {std::tuple<int,int,int,int>(255,19,21,255)};
    float timeRecover {0.f};
    bool puedeDisparar {true};
    float timeAnimation {0.f};
    float timeRespawn {0.f};

public:
    Enemy(Hp_t* hp, int damage, Sprite_t *spEnemy, IA *comportamiento); //Enemy pursuit y patrol
    Enemy(Hp_t* hp, int damage, Sprite_t *spEnemy, IA *comportamiento, int tipoMagia, float cadenciaDisparo); // Enemy shooter
    ~Enemy();

    void moveEnemyPatrol();
    void moveEnemyPursuit(Player_t *pl, bool colisiona);
    Disparo* dispararEnemy(Player_t *pl, bool colisiona);
    void checkReceive_damage();

    EntityID_t getID();

    Hp_t* getHp();
    void setHp(Hp_t* hp);

    int getDamage();
    void setDamage(int damage);

    float getVelocity();
    void setVelocity(float velocity);

    Sprite_t* getSprite();
    void setSprite(Sprite_t *spEnemy);

    IA* getComportamiento();
    void setComportamiento(IA *ia);

    int getTipoMagia();
    void setTipoMagia(int tipoMagia);

    bool getPuedeDisparar();
    void setPuedeDisparar(bool puedeDisparar);

    float getCadenciaDisparo();
    void setCadenciaDisparo(float cadenciaDisparo);
    
    std::pair<float,float> getPositionInit();
    void setPositionInit(std::pair<float,float> posicionInicial);

    int getPatrolPosition();
    void setPatrolPosition(int posicionVector);

    void setEnemy(Personajes s);
    Personajes getEnemy();

    bool getReceive_damage();
    void setReceive_damage(bool receive_damage);

    Estado_Personaje getEstadoEnemy();
    void setEstado(Estado_Personaje s);
    void setEstado_after_dead(Estado_Personaje s);

    float getTimeAnimation();
    void updateTimeAnimation();
    void setTimeAnimation(float newTime);

    float getTimeRespawn();
    void updateTimeRespawn();
    void setTimeRespawn(float newTime);
};
