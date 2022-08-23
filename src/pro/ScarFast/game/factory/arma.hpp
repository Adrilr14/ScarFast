#pragma once

#include "sprite.hpp"
#include "util.hpp"

class Player_t;
class Disparo;
class Temporizador_t;

// Enumeración para saber que tipo de arma es
enum TipoArma {espada = 0, magia = 1};

class Arma{

private:
    EntityID_t entityID { ++nextID };
	inline static EntityID_t nextID {0};
    int damage;
    Sprite_t* sp;
    int tipoMagia;
    float velocity;
    int tipoArma;
    int cargas;
    int max_cargas;
    float cadencia;

    // Auxuiliares
    float recarga {0.f};
    float timeCountdown {0.f};

public:
    Arma(int damage, Sprite_t *spArma, float cadencia = 1.5f); // Constructor de Espada
    Arma(int damage, Sprite_t *spArma, int tipoMagia, float vel = 350.f, int cargas = 3, int max_cargas = 3, float cadencia = 2.f); // Constructor de Magia
    ~Arma();

    Disparo* disparar(Player_t*);
    void recargar();

    Sprite_t* getSprite();
    void setSprite(Sprite_t *spArma);

    int getDamage();
    void setDamage(int damage);

    int getTipoMagia();
    void setTipoMagia(int tipoMagia);

    float getVelocity();
    void setVelocity(float velocity);

    int getTipoArma();
    void setTipoArma(int tipoArma);

    int getCargas();
    void setCargas(int carga);

    int getMaxCargas();
    void setMaxCargas(int maxCarga);

    float getCadencia();
    void setCadencia(float cadencia);

    float getTimeCountdown();
    void updateTimeCountdown();
    void setTimeCountdown(float time);

};