#pragma once

#include <string>
#include "../game/factory/util.hpp"
#include "SFML/Graphics.hpp"
class Keyboard_t;
class Sprite_t;
class Player_t;

struct Controller_t {
    
    virtual ~Controller_t() = default;
    virtual void createWindow() = 0;
    virtual bool isWindowOpen() = 0;
    virtual float getTemporizador() = 0; 
    virtual void resetTemporizador() = 0;
    virtual float getTimeElapsed() = 0;
    virtual void calculateDeltaTime() = 0;
    virtual float getDeltaTime() = 0;
    virtual void restartClock() = 0;
    virtual void showTemporizador(int min, int seg) = 0;
    virtual void run() = 0;
    virtual void check_Keyboard(Keyboard_t*) = 0;
    virtual void loadLevel() = 0;
    virtual void loadPlayers() = 0;
    virtual void loadEnemies() = 0;
    virtual void createShoot(EntityID_t id, Sprite_t*) = 0;
    virtual void create_spikes_p_one() = 0;
    virtual void create_spikes_p_two() = 0;
    virtual void destroyShoot(EntityID_t id) = 0;
    virtual void destroy_spikes(EntityID_t id) = 0;
    virtual void shoot(EntityID_t id, float posx, float posy) = 0;
    virtual bool checkCollisionKit(int id) = 0;
    virtual std::pair<EntityID_t, bool> checkCollisionPowerUps(int id) = 0;
    virtual void create_powerups_sfml() = 0;
    virtual void reset_power_ups() = 0;
    virtual bool checkCollisionRespawn(int id) = 0;
    virtual bool checkCollision(int i, int j, int id) = 0;
    virtual bool checkCollisionSpikes(int id) = 0;
    virtual bool checkCollisionRange(EntityID_t idPlayer, EntityID_t idEnemy) = 0;
    virtual bool checkCollisionEnemyPlayer(EntityID_t idPlayer, EntityID_t idEnemy) = 0;
    virtual bool checkCollisionDisparo(int i, int j,EntityID_t id) = 0;
    virtual bool checkCollisionDisparoPlayerAndEnemy(int id) = 0;
    virtual void attackmele(Player_t* p) = 0;
    virtual void animate_frame(Sprite_t* s,int id) = 0;
    virtual void revertAnimation(Player_t* p) = 0;
    virtual void createHUD() = 0;
    virtual void updateHUD() = 0;

    //Menu init
    virtual void initMenu() = 0;
    virtual void getInputMenu() = 0;
    virtual void updateMenu() = 0;

    virtual void initMenuJugar() = 0;
    virtual void getInputMenuJugar() = 0;
    virtual void updateMenuJugar() = 0;

    //virtual sf::RenderWindow getVentana() = 0;
    
    //Game
    virtual void initGame() = 0;
    virtual void getInputGame() = 0;
    virtual void updateGame() = 0;
    virtual std::tuple<int,int,int,int> setColorPlayer(int idPlayer, std::tuple<int,int,int,int> color) = 0;
    virtual std::tuple<int,int,int,int> setColorEnemy(int idEnemy, std::tuple<int,int,int,int> color) = 0;

    //Controlls
    virtual void initMenuControles() = 0;
    virtual void getInputMenuControles() = 0;
    virtual void updateMenuControles() = 0;

    //Credits
    
};
