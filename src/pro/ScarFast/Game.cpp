#include "Game.hpp"
#include "facade/ControllerMan.hpp"
#include "facade/MenuJugar.hpp"
#include "State/StateInit.hpp"
#include "State/StateGame.hpp"
#include "State/StateMenuPlay.hpp"
#include "State/StateControles.hpp"
#include <iostream>

Game_t::~Game_t() {

} 

Game_t* Game_t::game = 0;
Game_t* Game_t::getInstance() {
    if(game == 0) {
        game = new Game_t();
    }
    return game;
}

void Game_t::setState(State_t::State_type newState) {
    switch (newState){
        case State_t::State_type::INIT:
            estado = new StateInit_t(renderEngine);
        break;

        case State_t::State_type::INGAME:
            estado = new StateGame_t(renderEngine);
        break;
        case State_t::State_type::MPLAY:
            estado = new StateMenuPlay(renderEngine);
            break;
        case State_t::State_type::CONTROLS:
            estado = new StateControles(renderEngine);
            break;
        default:

        break;

    }
    estado->init();
}

// Función para crear los enemigos de tipo shooter
void Game_t::crearEnemigosShooter() 
{
    for (unsigned int x = 0; x < map->getEnemiesShoot().size(); x++)
    {
        auto posX = std::get<0>(map->getEnemiesShoot()[x]);
        auto posY = std::get<1>(map->getEnemiesShoot()[x]);
        auto width = std::get<2>(map->getEnemiesShoot()[x]);
        auto height = std::get<3>(map->getEnemiesShoot()[x]);
        IA *ia = new IA(std::pair<float,float>(width, height), TipoIA::shooter);
        Hp_t* hp = new Hp_t(40);
        int damage = 20;
        Physics_t *ph = new Physics_t(posX, posY, 250.0, 250.0);
        Sprite_t *sp = new Sprite_t("resources/Mapas/Mapa_1/Sprites/enemigo1.png", 40, 40, ph);
        int tipoMagia = 0;
        float cadencia = 3.0;
        Enemy *e = new Enemy(hp, damage, sp, ia, tipoMagia, cadencia);
        e->setEnemy(Personajes::enemigo3);
        enemies.push_back(e);
    }
        animations->load_animations("resources/Animations/enemigo1.json");
}

// Función para crear los enemigos de tipo patrol
void Game_t::crearEnemigosPatrol() 
{
    for (unsigned int x = 0; x < map->getEnemiesPatrol().size(); x++)
    {
        // Metemos las posiciones del patrón en un vector que limpiamos al final de crear un enemigo
        std::vector<std::pair<float,float>> patrol;
        for (unsigned int y = 0; y < map->getEnemiesPatrol()[x].size(); y++)
        {
            auto posX = map->getEnemiesPatrol()[x][y].first;
            auto posY = map->getEnemiesPatrol()[x][y].second;
            patrol.push_back(std::pair<float,float>(posX, posY));
        }
        
        auto posX = map->getEnemiesPatrol()[x][0].first;
        auto posY = map->getEnemiesPatrol()[x][0].second;
        IA *ia = new IA(patrol);
        Hp_t* hp = new Hp_t(60);
        int damage = 20;
        Physics_t *ph = new Physics_t(posX, posY, 120.0, 120.0);
        Sprite_t *sp = new Sprite_t("resources/Mapas/Mapa_1/Sprites/enemigo2.png", 40, 40, ph);
        Enemy *e = new Enemy(hp, damage, sp, ia);
        e->setEnemy(Personajes::enemigo2);
        enemies.push_back(e);
        patrol.clear();
    }
    animations->load_animations("resources/Animations/enemigo2.json");
}

// Función para crear los enemigos de tipo pursuit
void Game_t::crearEnemigosPursuit() 
{
    for (unsigned int x = 0; x < map->getEnemiesPursuit().size(); x++)
    {
        auto posX = std::get<0>(map->getEnemiesPursuit()[x]);
        auto posY = std::get<1>(map->getEnemiesPursuit()[x]);
        auto width = std::get<2>(map->getEnemiesPursuit()[x]);
        auto height = std::get<3>(map->getEnemiesPursuit()[x]);
        IA *ia = new IA(std::pair<float,float>(width, height), TipoIA::pursuit);
        Hp_t* hp = new Hp_t(50);
        int damage = 20;
        Physics_t *ph = new Physics_t(posX, posY, 120.0, 120.0);
        Sprite_t *sp = new Sprite_t("resources/Mapas/Mapa_1/Sprites/enemigo3.png", 40, 40, ph);
        Enemy *e = new Enemy(hp, damage, sp, ia);
        e->setEnemy(Personajes::enemigo1);
        enemies.push_back(e);
    }
    animations->load_animations("resources/Animations/enemigo3.json");
}

// Función para crear los enemigos
void Game_t::crearEnemigos()
{
    enemies.resize(0); // Cambiamos el size del vector de enemigos a 0 para meterlos
    // Creamos los diferentes tipos de enemigos
    crearEnemigosShooter();
    crearEnemigosPatrol();
    crearEnemigosPursuit();
}

void Game_t::InitGame() {

    renderEngine = &ControllerMan::instancia().controller();
    renderEngine->createWindow();

    map = new Map_t();
    animations = new Animation_t();

    if(MenuJugar::getJugador1() == 0)
    {
        Arma* espadaP1 = new Arma(50, new Sprite_t); // Espada P1
        one = new Player_t("resources/Mapas/Mapa_1/Sprites/minotauro.png",40,40,espadaP1);
        one->setPersonaje(Personajes::minotauro);
    }
    else
    {
        Arma* magiaP1 = new Arma(20, new Sprite_t, 0); // Magia P1
        one = new Player_t("resources/Mapas/Mapa_1/Sprites/golem.png",40,40,magiaP1);
        one->setPersonaje(Personajes::golem);
    }

    if(MenuJugar::getJugador2() == 0)
    {
        Arma* espadaP2 = new Arma(50, new Sprite_t); // Espada P1
        two = new Player_t("resources/Mapas/Mapa_1/Sprites/minotauro.png",40,40,espadaP2);
        two->setPersonaje(Personajes::minotauro);
    }
    else
    {
        Arma* magiaP2 = new Arma(20, new Sprite_t, 0); // Magia P1
        two = new Player_t("resources/Mapas/Mapa_1/Sprites/golem.png",40,40,magiaP2);
        two->setPersonaje(Personajes::golem);
    }
    
    keyboard = new Keyboard_t();
    std::srand(std::time(nullptr));
    map->loadMap(3+rand()%4);
    animations->load_animations("resources/Animations/minotauro.json");
    animations->load_animations("resources/Animations/golem.json");
    crearEnemigos(); // Creamos los enemigos
    Power_Up::create_powerUp_for_the_map();
    renderEngine->loadLevel();
    renderEngine->loadPlayers();
    renderEngine->loadEnemies();

    one->getSprite()->getPhysics()->x = map->getRespawn_one()->getPhysics()->x;
    one->getSprite()->getPhysics()->y = map->getRespawn_one()->getPhysics()->y;

    two->getSprite()->getPhysics()->x = map->getRespawn_two()->getPhysics()->x;
    two->getSprite()->getPhysics()->y = map->getRespawn_two()->getPhysics()->y;

    ronda = new Ronda_t(Max_rondas::ronda_min);

    hud = new Hud("resources/HUD.png",map->getHud());
    hud->display_hud();

    setState(State_t::INIT);

    one->getHp()->setHp(100);
    two->getHp()->setHp(100);
}

void Game_t::MainLoop() {
    while(renderEngine->isWindowOpen()) {
        if(renderEngine->getTimeElapsed() >= tiempoJuego){
            estado->update();
            estado->getInput();
            tiempoJuego = renderEngine->getTimeElapsed() + (1.f/60.f);
            renderEngine->calculateDeltaTime();
        }
    }
}

Hud* Game_t::getHud(){
    return hud;
}

Map_t* Game_t::getMap() {
    return this->map;
}

Player_t* Game_t::getPlayerOne() {
    return one;
}

Player_t* Game_t::getPlayerTwo() {
    return two;
}

Keyboard_t* Game_t::getKeyboard() {
    return keyboard;
}

Ronda_t* Game_t::getRonda() {
    return ronda;
}

State_t* Game_t::getState() {
    return estado;
}

Temporizador_t* Game_t::getTemporizador() {
    return temporizador;
}

Animation_t* Game_t::getAnimation() {
    return animations;
}

std::vector<Enemy*> Game_t::getEnemies() {
    return enemies;
}

bool Game_t::getGameStart(){
    return gameStarting;
}

void Game_t::setTemporizador(Temporizador_t* t){
    temporizador = t;
}

void Game_t::setGameStart(bool b){
    gameStarting = b;
}
