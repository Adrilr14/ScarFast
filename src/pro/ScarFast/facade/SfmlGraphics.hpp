#pragma once

#include <SFML/Graphics.hpp>

#include "Controller.hpp"
#include "Menu.hpp"
#include "MenuJugar.hpp"
#include "MenuControles.hpp"
#include "../game/factory/util.hpp"

#include <vector>
#include <map>

class Keyboard_t;
class Sprite_t;
class Player_t;
class Enemy;

struct SfmlGraphics : public Controller_t {

private:
    sf::RenderWindow *window;
    sf::Texture* textureMap;
    std::vector<std::vector<sf::Sprite*>> spritessfml;
    sf::Sprite* sprone;
    sf::Sprite* sprtwo;
    sf::Sprite* sprBackground;

    sf::Texture* textureone;
    sf::Texture* texturetwo;
    sf::Texture* textBackground;

    sf::Texture* objects;

    sf::Sprite* respawn_one;
    sf::Sprite* respawn_two;

    sf::Sprite* kit;

    sf::Texture* arma;

    sf::Texture* hud;
    std::vector<sf::Sprite*> hud_items;
    std::map<int, sf::Sprite*> hud_one;
    std::map<int, sf::Sprite*> hud_two;
    

    std::map<EntityID_t,sf::Sprite*> disparos;    
    std::map<EntityID_t, sf::Sprite*> powerUps;
    std::vector<sf::Sprite*> spikes_1;
    std::vector<sf::Sprite*> spikes_2;
    std::map<EntityID_t,sf::Sprite*> enemigos;
    std::map<EntityID_t,sf::Texture*> texturasEnemigos;
    std::map<EntityID_t,sf::RectangleShape*> rangos;
    std::map<EntityID_t,int> idPlayerAtacar; // 0 = ninguno; 1 = player 1; 2 = player 2;

    //Tamanyo pantalla
    int widthScreen     {1920};
    int heightScreen    {1080};

    sf::Clock* time;

    int aux = 0, aux2 = 0, auxColor = 0;
    bool comprobacion = true;

    sf::View vista;
    sf::View vistaHUD;
    sf::RenderTexture renderHUD;
    sf::Sprite header;

    float temporizador;
    float elapsedTimeFrameAnterior {0.f};
    float deltaTime {0.f};
    float count  {-1};
    float count_ {-1};
    sf::Font alarmClock;
    sf::Font brawl;
    sf::Text j1;
    sf::Text j2;
    sf::Text ronda;
    sf::Sprite* pw1 {nullptr};
    sf::Sprite* pw2 {nullptr};
    sf::Sprite* mini_kit {nullptr};
    sf::Text textoTempo;
    float distanciActual;
    float distanciAnterior;
    int pospw_1;
    int pospw_2;

    sf::RectangleShape transparencia;

    int fps {60};

    //Menus
    Menu* menu;
    MenuJugar* mPlay;
    MenuControles* mCont;

    // Functions
    void dispararEnemigosIAShooter(Enemy* enemy, Player_t* player1, Player_t* player2, int id);
    void moverEnemigosIAPatrol(Enemy* enemy, int id);
    void moverEnemigosIAPursuit(Enemy* enemy, Player_t* player1, Player_t* player2, int id);

public:
    SfmlGraphics(){};
    virtual ~SfmlGraphics(){};
    void createWindow() override;
    bool isWindowOpen() override;
    float getTimeElapsed() override;
    void calculateDeltaTime() override;
    float getDeltaTime() override;
    float getTemporizador() override;
    void resetTemporizador() override;
    void restartClock() override;
    void showTemporizador(int min, int seg) override;
    void run() override;
    void check_Keyboard(Keyboard_t*) override;
    void loadLevel() override;
    void loadPlayers() override;
    void loadEnemies() override;
    void createShoot(EntityID_t id, Sprite_t* spr) override;
    void create_spikes_p_one() override;
    void create_spikes_p_two() override;
    void destroyShoot(EntityID_t id) override;
    void destroy_spikes(EntityID_t id) override;
    void shoot(EntityID_t id, float posx, float posy) override;
    bool checkCollisionKit(int id) override;
    std::pair<EntityID_t,bool> checkCollisionPowerUps(int id);
    void create_powerups_sfml() override;
    void reset_power_ups() override;
    bool checkCollisionRespawn(int id) override;
    bool checkCollision(int i, int j, int id) override;
    bool checkCollisionSpikes(int id) override;
    bool checkCollisionRange(EntityID_t idPlayer, EntityID_t idEnemy) override;
    bool checkCollisionEnemyPlayer(EntityID_t idPlayer, EntityID_t idEnemy) override;
    bool checkCollisionDisparo(int i, int j,EntityID_t id)  override;
    bool checkCollisionDisparoPlayerAndEnemy(int id) override;
    void attackmele(Player_t* p) override;
    void select_frame(sf::Sprite* s,Player_t* pl);
    void select_frameEnemy(sf::Sprite* s,Enemy* e);
    void animate_frame(Sprite_t* s,int id) override;
    void animatedEnemies(Enemy* enemigo);
    void revertAnimation(Player_t* p) override;
    void createHUD() override;
    void updateHUD() override;

    //InitMenu
    void initMenu() override;
    void getInputMenu() override;
    void updateMenu() override;

    void initMenuJugar();
    void getInputMenuJugar();
    void updateMenuJugar();
    
    void initMenuControles() ;
    void getInputMenuControles() ;
    void updateMenuControles() ;

    //sf::RenderWindow getVentana() override;

    //Game
    void initGame() override;
    void getInputGame() override;
    void updateGame() override;
    std::tuple<int,int,int,int> setColorPlayer(int idPlayer, std::tuple<int,int,int,int> color) override;
    std::tuple<int,int,int,int> setColorEnemy(int idEnemy, std::tuple<int,int,int,int> color) override;

    void camara();
};

