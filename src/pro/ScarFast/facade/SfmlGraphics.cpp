#include "SfmlGraphics.hpp"
#include "../Game.hpp"
#include "../game/factory/util.hpp"
#include "../game/factory/map.hpp"
#include "../game/factory/player.hpp"
#include "../game/factory/enemy.hpp"
#include "../game/factory/disparo.hpp"
#include "../game/sys/input.hpp"
#include <math.h>
#include <iostream>

void SfmlGraphics::createWindow() {
    //sf::Style::Fullscreen
    window = new sf::RenderWindow(sf::VideoMode(widthScreen,heightScreen),"ScarFast",sf::Style::Fullscreen);
    time = new sf::Clock();
    //renderHUD.create(widthScreen+30,80);
    vista = window->getView();


    // 80 es 4 sprites por 20 que miden en px
    vista.setCenter((widthScreen)/2,heightScreen/2);
    vista.setSize(widthScreen,heightScreen);

    //vistaHUD.setCenter(80/2, heightScreen/2);
    //vistaHUD.setSize(80, heightScreen);


    window->setFramerateLimit(fps);
}

void SfmlGraphics::loadLevel() {
    Map_t* mapa = Game_t::getInstance()->getMap();

    textureMap = new sf::Texture();
    textBackground = new sf::Texture();
    if(textBackground->loadFromFile(mapa->getBackGround()->getRoute())) {
        sprBackground = new sf::Sprite(*textBackground);
        sprBackground->setPosition(mapa->getBackGround()->getPhysics()->x,mapa->getBackGround()->getPhysics()->y);
    }
    spritessfml.resize(mapa->getHeightMap(), std::vector<sf::Sprite*>(mapa->getWithMap()));
    if(textureMap->loadFromFile("resources/Mapas/Mapa_"+std::to_string(mapa->number_mapa)+"/Sprites/tileMap_"+std::to_string(mapa->number_mapa)+".png")){
        for(unsigned int i = 0; i < mapa->getMatrizMapa().size();i++){
            for(unsigned int j = 0; j < mapa->getMatrizMapa()[i].size(); j++) {
                sf::Sprite* spr = new sf::Sprite(*textureMap);

                if(mapa->getMatrizMapa()[i][j]) {
                    spr->setOrigin(
                        mapa->getMatrizMapa()[i][j]->getWidth()/2,
                        mapa->getMatrizMapa()[i][j]->getHeight()/2
                    );

                    spr->setTextureRect(
                        sf::IntRect((mapa->getMatrizMapa()[i][j]->getID()-1) * 20
                        , 0 , 
                        mapa->getMatrizMapa()[i][j]->getWidth(), 
                        mapa->getMatrizMapa()[i][j]->getHeight())
                    );

                    spr->setPosition(
                        mapa->getMatrizMapa()[i][j]->getPhysics()->x,
                        mapa->getMatrizMapa()[i][j]->getPhysics()->y
                    );
                    spritessfml[i][j] = spr;
                }
            }
        }

        objects = new sf::Texture();
        if(objects->loadFromFile("resources/Mapas/Mapa_1/Sprites/tile_map_1_objects.png")){
            respawn_one = new sf::Sprite(*objects);
            respawn_one->setOrigin(
                mapa->getRespawn_one()->getWidth()/2,
                mapa->getRespawn_one()->getHeight()/2
            );

            respawn_one->setTextureRect(
                    sf::IntRect(0 * 34
                    , 0 , 
                    mapa->getRespawn_one()->getWidth(), 
                    mapa->getRespawn_one()->getHeight())
            );

            respawn_one->setPosition(
                    mapa->getRespawn_one()->getPhysics()->x,
                    mapa->getRespawn_one()->getPhysics()->y
            );


            respawn_two = new sf::Sprite(*objects);
            respawn_two->setOrigin(
                mapa->getRespawn_two()->getWidth()/2,
                mapa->getRespawn_two()->getHeight()/2
            );

            respawn_two->setTextureRect(
                    sf::IntRect(1 * 34
                    , 0 , 
                    mapa->getRespawn_two()->getWidth(), 
                    mapa->getRespawn_two()->getHeight())
            );

            respawn_two->setPosition(
                    mapa->getRespawn_two()->getPhysics()->x,
                    mapa->getRespawn_two()->getPhysics()->y
            );

            kit = new sf::Sprite(*objects);

            kit->setOrigin(
                mapa->getKit()->getWidth()/2,
                mapa->getKit()->getHeight()/2
            );

            kit->setTextureRect(
                sf::IntRect(34 * 2
                , 0 , 
                mapa->getKit()->getWidth(), 
                mapa->getKit()->getHeight())
            );

            kit->setPosition(
                mapa->getKit()->getPhysics()->x,
                mapa->getKit()->getPhysics()->y
            );

            kit->setScale(2,2);

            create_powerups_sfml();
        }
    }
}

void SfmlGraphics::create_powerups_sfml() {
    Map_t* mapa = Game_t::getInstance()->getMap();
    for(unsigned int i = 0; i < mapa->getPowerUps().size(); i++){
        if(mapa->getPowerUps()[i]->getActivate() && mapa->getPowerUps()[i]->getSprite()->getVisible() == State_v::visible){
            sf::Sprite* spw = new sf::Sprite(*objects);
            spw->setOrigin(
                mapa->getPowerUps()[i]->getSprite()->getWidth()/2,
                mapa->getPowerUps()[i]->getSprite()->getHeight()/2
            );

            spw->setTextureRect(
                sf::IntRect(2 * 34 + 17 
                , 0 , 
                mapa->getPowerUps()[i]->getSprite()->getWidth(),
                mapa->getPowerUps()[i]->getSprite()->getHeight())
            );

            spw->setPosition(
                mapa->getPowerUps()[i]->getSprite()->getPhysics()->x,
                mapa->getPowerUps()[i]->getSprite()->getPhysics()->y
            );
            powerUps.emplace(mapa->getPowerUps()[i]->getID(),spw);
        }    
    }  
}

void SfmlGraphics::loadPlayers() {
    Player_t* playerone = Game_t::getInstance()->getPlayerOne();
    Player_t* playertwo = Game_t::getInstance()->getPlayerTwo();
    
    if(playerone != nullptr && playertwo != nullptr) {
        std::string textura = playerone->getSprite()->getRoute();
        textureone = new sf::Texture();
        if(textureone->loadFromFile(textura)) {
            sprone = new sf::Sprite(*textureone);

            sprone->setOrigin(
                playerone->getSprite()->getWidth()/2,
                playerone->getSprite()->getHeight()/2
            );
        
            select_frame(sprone,playerone);

            sprone->setPosition(
                playerone->getSprite()->getPhysics()->x,
                playerone->getSprite()->getPhysics()->y
            );   
            
        }

        textura = playertwo->getSprite()->getRoute();
        texturetwo = new sf::Texture();
        if(texturetwo->loadFromFile(textura)) {
            sprtwo = new sf::Sprite(*texturetwo);
            
            sprtwo->setOrigin(
                playertwo->getSprite()->getWidth()/2,
                playertwo->getSprite()->getHeight()/2
            );

            select_frame(sprtwo,playertwo);

            sprtwo->setPosition(
                playertwo->getSprite()->getPhysics()->x,
                playertwo->getSprite()->getPhysics()->y
            );
        }
    }   
}

void SfmlGraphics::loadEnemies() 
{
    auto enemigos_sfml = Game_t::getInstance()->getEnemies();

    for (unsigned int x = 0; x < enemigos_sfml.size(); x++)
    {
        if(enemigos_sfml[x] != NULL){
            std::string textura = enemigos_sfml[x]->getSprite()->getRoute();
            texturasEnemigos[x] = new sf::Texture();
            if(texturasEnemigos[x]->loadFromFile(textura)) {
                enemigos[x] = new sf::Sprite(*texturasEnemigos[x]);

                enemigos[x]->setOrigin(
                    enemigos_sfml[x]->getSprite()->getWidth()/2,
                    enemigos_sfml[x]->getSprite()->getHeight()/2
                );

                enemigos[x]->setPosition(
                    enemigos_sfml[x]->getSprite()->getPhysics()->x,
                    enemigos_sfml[x]->getSprite()->getPhysics()->y
                );
                
                auto width = enemigos_sfml[x]->getComportamiento()->getRange().first;
                auto height = enemigos_sfml[x]->getComportamiento()->getRange().second;
                rangos[x] = new sf::RectangleShape(sf::Vector2f(width, height));

                rangos[x]->setOrigin(
                    width/2,
                    height/2
                );

                rangos[x]->setPosition(
                    enemigos_sfml[x]->getSprite()->getPhysics()->x,
                    enemigos_sfml[x]->getSprite()->getPhysics()->y
                );

                idPlayerAtacar[x] = 0;
            }
        }
    }
}

bool SfmlGraphics::isWindowOpen() {
    return window->isOpen();
}

float SfmlGraphics::getTimeElapsed() {
    return time->getElapsedTime().asSeconds();
}

void SfmlGraphics::calculateDeltaTime() {
    deltaTime = time->getElapsedTime().asSeconds() - elapsedTimeFrameAnterior;
    elapsedTimeFrameAnterior = time->getElapsedTime().asSeconds();
}

float SfmlGraphics::getDeltaTime() {
    return deltaTime;
} 

float SfmlGraphics::getTemporizador() {
    temporizador += time->getElapsedTime().asSeconds();
    return temporizador;
}

void SfmlGraphics::resetTemporizador() {
    temporizador = 0;
}

void SfmlGraphics::restartClock() {
    time->restart();
}

void SfmlGraphics::showTemporizador(int min, int seg) {
    alarmClock.loadFromFile("resources/fonts/alarmclock/alarmclock.ttf");
    textoTempo.setFont(alarmClock);
    if(min > 0 || seg >= 0){
        if(seg < 10){
            textoTempo.setString(std::to_string(min) + ":0" + std::to_string(seg));
        }else{
            textoTempo.setString(std::to_string(min) + ":" + std::to_string(seg));
        }
        textoTempo.setColor(sf::Color::Red);
        textoTempo.setScale(1,1);
        textoTempo.setPosition((widthScreen/2)-20,heightScreen/8);
    }else{
        //Desrtruimos el temporizador
        Game_t::getInstance()->setTemporizador(nullptr);
    }
}

// Función para comprobar en el run() si un enemigo shooter tiene que disparar
void SfmlGraphics::dispararEnemigosIAShooter(Enemy* e, Player_t* p1, Player_t* p2, int id) 
{
    bool colisionaP1 = checkCollisionRange(ID_PLAYER_ONE, e->getID());
    bool colisionaP2 = checkCollisionRange(ID_PLAYER_TWO, e->getID());
    
    if(colisionaP1 && colisionaP2)
    {
        idPlayerAtacar[id] = 1 + rand()%2;
        if(idPlayerAtacar[id] == 1) 
        {
            auto* disp = e->dispararEnemy(p1, colisionaP1);
            if(disp) Map_Disparos::disparos.insert({disp->getEntity(),disp});
        }
        if(idPlayerAtacar[id] == 2) 
        {
            auto* disp = e->dispararEnemy(p2, colisionaP2);
            if(disp) Map_Disparos::disparos.insert({disp->getEntity(),disp});
        }
    }
    else if(colisionaP1)
    {
        idPlayerAtacar[id] = ID_PLAYER_ONE;
        auto* disp = e->dispararEnemy(p1, colisionaP1);
        if(disp) Map_Disparos::disparos.insert({disp->getEntity(),disp});
    }
    else if(colisionaP2)
    {
        idPlayerAtacar[id] = ID_PLAYER_TWO;
        auto* disp = e->dispararEnemy(p2, colisionaP2);
        if(disp) Map_Disparos::disparos.insert({disp->getEntity(),disp});
    }
    else
    {
        e->dispararEnemy(p1, colisionaP1);
    }
}

// Función para comprobar en el run() si un enemigo pursuit tiene que perseguir al jugador o volver a su posición
void SfmlGraphics::moverEnemigosIAPatrol(Enemy* e, int id) 
{
    e->moveEnemyPatrol();
    // Actualizamos la posición de los enemigos
    enemigos[id]->setPosition(
        e->getSprite()->getPhysics()->x,
        e->getSprite()->getPhysics()->y
    );
}

// Función para mover a un enemigo patrol en el run()
void SfmlGraphics::moverEnemigosIAPursuit(Enemy* e, Player_t* p1, Player_t* p2, int id) 
{
    bool colisionaP1 = checkCollisionRange(ID_PLAYER_ONE, e->getID());
    bool colisionaP2 = checkCollisionRange(ID_PLAYER_TWO, e->getID());
    if(idPlayerAtacar[id] == 0)
    {
        if(colisionaP1)
        {
            idPlayerAtacar[id] = ID_PLAYER_ONE;
            e->moveEnemyPursuit(p1, colisionaP1);
        }
        else if(colisionaP2)
        {
            idPlayerAtacar[id] = ID_PLAYER_TWO;
            e->moveEnemyPursuit(p2, colisionaP2);
        }
        else
        {
            e->moveEnemyPursuit(p1, colisionaP1);
        }
    }
    else if(idPlayerAtacar[id] == ID_PLAYER_ONE)
    {
        if(colisionaP1)
        {
            idPlayerAtacar[id] = ID_PLAYER_ONE;
            e->moveEnemyPursuit(p1, colisionaP1);
        }
        else if(colisionaP2)
        {
            idPlayerAtacar[id] = ID_PLAYER_TWO;
            e->moveEnemyPursuit(p2, colisionaP2);
        }
        else
        {
            idPlayerAtacar[id] = 0;
            e->moveEnemyPursuit(p1, colisionaP1);
        }
    }
    else if(idPlayerAtacar[id] == ID_PLAYER_TWO)
    {
        if(colisionaP2)
        {
            e->moveEnemyPursuit(p2, colisionaP2);
        }
        else if(colisionaP1)
        {
            idPlayerAtacar[id] = ID_PLAYER_ONE;
            e->moveEnemyPursuit(p1, colisionaP1);
        }
        else
        {
            idPlayerAtacar[id] = 0;
            e->moveEnemyPursuit(p1, colisionaP1);
        }
    }
    // Actualizamos la posición de los enemigos
    enemigos[id]->setPosition(
        e->getSprite()->getPhysics()->x,
        e->getSprite()->getPhysics()->y
    );
}



void SfmlGraphics::run() {

    //window->clear();

    auto* mapa = Game_t::getInstance()->getMap();
    header.setPosition(window->mapPixelToCoords({0,0}));

    //Bucle de obtención de eventos
    Player_t* playerone = Game_t::getInstance()->getPlayerOne();
    Player_t* playertwo = Game_t::getInstance()->getPlayerTwo();
    //Hud* hud = Game_t::getInstance()->getHud();
    Physics_t* p;

    sf::Event event;
    while(window->pollEvent(event)) {
        Game_t::getInstance()->getKeyboard()->restart_keyboard();
        check_Keyboard(Game_t::getInstance()->getKeyboard());
    }
    sprone->setPosition(
        playerone->getSprite()->getPhysics()->x,
        playerone->getSprite()->getPhysics()->y
    );

    sprtwo->setPosition(
        playertwo->getSprite()->getPhysics()->x,
        playertwo->getSprite()->getPhysics()->y
    );

    // Movimiento, disparo y colisiones (con los jugadores) de los enemigos
    auto enemigos_sfml = Game_t::getInstance()->getEnemies();
    for(unsigned int i = 0; i < enemigos_sfml.size(); i++) 
    {
        if(enemigos_sfml[i] != nullptr) 
        {
            if(enemigos_sfml[i]->getComportamiento()->getTipoIA() == TipoIA::pursuit) 
            {
                moverEnemigosIAPursuit(enemigos_sfml[i], playerone, playertwo, i);
                bool atacaP1 = checkCollisionEnemyPlayer(ID_PLAYER_ONE, enemigos_sfml[i]->getID());
                bool atacaP2 = checkCollisionEnemyPlayer(ID_PLAYER_TWO, enemigos_sfml[i]->getID());
                if(atacaP1 && !playerone->getReceive_damage() && playerone->getEstado() != Estado_Personaje::atacar && playerone->getEstado() != Estado_Personaje::morir && enemigos_sfml[i]->getEstadoEnemy() != Estado_Personaje::morir)
                {   
                    if(enemigos_sfml[i]->getEstadoEnemy() != Estado_Personaje::atacar) enemigos_sfml[i]->setEstado(Estado_Personaje::atacar);
                    if(enemigos_sfml[i]->getEstadoEnemy() == Estado_Personaje::atacar)
                    {
                        playerone->getHp()->reduceHp(enemigos_sfml[i]->getDamage());
                        if (playerone->getHp()->getHp() > 0)
                        {
                            playerone->setReceive_damage(true);
                        }
                    }
                }
                else if(atacaP2 && !playertwo->getReceive_damage() && playertwo->getEstado() != Estado_Personaje::atacar && playertwo->getEstado() != Estado_Personaje::morir && enemigos_sfml[i]->getEstadoEnemy() != Estado_Personaje::morir)
                {
                    if(enemigos_sfml[i]->getEstadoEnemy() != Estado_Personaje::atacar) enemigos_sfml[i]->setEstado(Estado_Personaje::atacar);
                    playertwo->getHp()->reduceHp(enemigos_sfml[i]->getDamage());
                    if(enemigos_sfml[i]->getEstadoEnemy() == Estado_Personaje::atacar)
                    {
                        if (playertwo->getHp()->getHp() > 0)
                        {
                            playertwo->setReceive_damage(true);
                        }
                    }
                }
                
            }
            else if(enemigos_sfml[i]->getComportamiento()->getTipoIA() == TipoIA::patrol)
            {
                moverEnemigosIAPatrol(enemigos_sfml[i], i);

                // Comprobamos si colisiona con el jugador para quitarle vida
                bool atacaP1 = checkCollisionEnemyPlayer(ID_PLAYER_ONE, enemigos_sfml[i]->getID());
                bool atacaP2 = checkCollisionEnemyPlayer(ID_PLAYER_TWO, enemigos_sfml[i]->getID());

                if(atacaP1 && !playerone->getReceive_damage() && playerone->getEstado() != Estado_Personaje::atacar && playerone->getEstado() != Estado_Personaje::morir && enemigos_sfml[i]->getEstadoEnemy() != Estado_Personaje::morir)
                {   
                    playerone->getHp()->reduceHp(enemigos_sfml[i]->getDamage());
                    if (playerone->getHp()->getHp() > 0)
                    {
                        playerone->setReceive_damage(true);
                    }
                }
                else if(atacaP2 && !playertwo->getReceive_damage() && playertwo->getEstado() != Estado_Personaje::atacar && playertwo->getEstado() != Estado_Personaje::morir && enemigos_sfml[i]->getEstadoEnemy() != Estado_Personaje::morir)
                {
                    playertwo->getHp()->reduceHp(enemigos_sfml[i]->getDamage());
                    if (playertwo->getHp()->getHp() > 0)
                    {
                        playertwo->setReceive_damage(true);
                    }
                }
            }
            else if(enemigos_sfml[i]->getComportamiento()->getTipoIA() == TipoIA::shooter)
            {
                dispararEnemigosIAShooter(enemigos_sfml[i], playerone, playertwo, i);
            }
            // Animación del enemigo
            animatedEnemies(enemigos_sfml[i]);
        }
    }

   
    //window->display();
}


void SfmlGraphics::check_Keyboard(Keyboard_t* key) {
    auto* p_one = Game_t::getInstance()->getPlayerOne();
    auto* p_two = Game_t::getInstance()->getPlayerTwo();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        key->key_Right = true;
        p_two->getDireccion()->dirPrevia = p_two->getDireccion()->dir;
        p_two->getDireccion()->dir = 1;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        key->key_Left = true;
        p_two->getDireccion()->dirPrevia = p_two->getDireccion()->dir;
        p_two->getDireccion()->dir = 2;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        key->key_Up = true;
        p_two->getDireccion()->dirPrevia = p_two->getDireccion()->dir;
        p_two->getDireccion()->dir = 4;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        key->key_Down = true;
        p_two->getDireccion()->dirPrevia = p_two->getDireccion()->dir;
        p_two->getDireccion()->dir = 3;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        key->key_W = true;
        p_one->getDireccion()->dirPrevia = p_one->getDireccion()->dir;
        p_one->getDireccion()->dir = 4;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        key->key_A = true;
        p_one->getDireccion()->dirPrevia = p_one->getDireccion()->dir;
        p_one->getDireccion()->dir = 2;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        key->key_S = true;
        p_one->getDireccion()->dirPrevia = p_one->getDireccion()->dir;
        p_one->getDireccion()->dir = 3;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        key->key_D = true;
        p_one->getDireccion()->dirPrevia = p_one->getDireccion()->dir;
        p_one->getDireccion()->dir = 1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
        key->key_Enter = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        key->key_Space = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
        key->key_shift_left = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
        key->key_shift_right = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        key->key_Esc = true;
    }
}

void SfmlGraphics::createShoot(EntityID_t id, Sprite_t* spr){
    arma = new sf::Texture();
    if(arma->loadFromFile(spr->getRoute())){
        sf::Sprite* sp = new sf::Sprite(*arma);
        sp->setOrigin(32 / 2, 32 / 2);
        //sp->setScale(0.5,0.5);
        sp->setPosition(spr->getPhysics()->x,spr->getPhysics()->y);
        this->disparos.insert({id,sp});
    }
}

void SfmlGraphics::create_spikes_p_one(){
    Map_t* mapa = Game_t::getInstance()->getMap();
    for(unsigned int i = 0; i < mapa->getSpikes_1().size(); i++){
        auto* spr = new sf::Sprite(*objects);
        spr->setOrigin(
            mapa->getSpikes_1()[i]->getWidth()/2,
            mapa->getSpikes_1()[i]->getHeight()/2
        );
        spr->setTextureRect(
            sf::IntRect(2 * 34 + 17 + 20
            , 0 , 
            mapa->getSpikes_1()[i]->getWidth(),
            mapa->getSpikes_1()[i]->getHeight())
        );
        spr->setPosition(
            mapa->getSpikes_1()[i]->getPhysics()->x,
            mapa->getSpikes_1()[i]->getPhysics()->y
        );
        spikes_1.push_back(spr);
    }
}

void SfmlGraphics::create_spikes_p_two(){
    Map_t* mapa = Game_t::getInstance()->getMap();
    for(unsigned int i = 0; i < mapa->getSpikes_2().size(); i++){
        auto* spr = new sf::Sprite(*objects);
        spr->setOrigin(
            mapa->getSpikes_2()[i]->getWidth()/2,
            mapa->getSpikes_2()[i]->getHeight()/2
        );
        spr->setTextureRect(
            sf::IntRect(2 * 34 + 17 + 20
            , 0 , 
            mapa->getSpikes_2()[i]->getWidth(),
            mapa->getSpikes_2()[i]->getHeight())
        );
        spr->setPosition(
            mapa->getSpikes_2()[i]->getPhysics()->x,
            mapa->getSpikes_2()[i]->getPhysics()->y
        );
        spikes_2.push_back(spr);
    }
}

void SfmlGraphics::destroyShoot(EntityID_t id){
    this->disparos.erase(id);
}

void SfmlGraphics::destroy_spikes(EntityID_t id) {
    if(id == ID_PLAYER_ONE) {
        for(unsigned int i = 0; i < spikes_1.size(); i++){
            spikes_1[i] = nullptr;
            delete spikes_1[i];
        }
        spikes_1.clear();
    }else{
        for(unsigned int i = 0; i < spikes_2.size(); i++){
            spikes_2[i] = nullptr;
            delete spikes_2[i];
        }
        spikes_2.clear();
    }
}

void SfmlGraphics::shoot(EntityID_t id, float posx, float posy){
    if(disparos[id] != nullptr)
        disparos[id]->setPosition(posx,posy);
}


bool SfmlGraphics::checkCollisionDisparoPlayerAndEnemy(int id) {
    bool colisiona = false;
    if(disparos[id] != nullptr)
    {
        if(Map_Disparos::disparos[id]->getObjetivo() == Objetivo::player_one)
        {
            // Colisión con jugador 1
            auto* player = Game_t::getInstance()->getPlayerOne();
            if(sprone->getGlobalBounds().intersects(disparos[id]->getGlobalBounds()))
            {
                if (player->getReceive_damage() == false && player->getEstado() != Estado_Personaje::morir)
                {
                    player->getHp()->reduceHp(Map_Disparos::disparos[id]->getDamage());
                    if (player->getHp()->getHp() > 0)
                    {
                        player->setReceive_damage(true);
                    }
                }
                colisiona = true;
            }
            // Colisión con enemigos
            auto enemigos_sfml = Game_t::getInstance()->getEnemies();
            for(unsigned int i = 0; i < enemigos_sfml.size(); i++) 
            {
                if(enemigos_sfml[i] != nullptr) 
                {
                    if(enemigos[i]->getGlobalBounds().intersects(disparos[id]->getGlobalBounds()) && enemigos_sfml[i]->getEstadoEnemy() != Estado_Personaje::morir)
                    {
                        if (enemigos_sfml[i]->getReceive_damage() == false)
                        {
                            enemigos_sfml[i]->getHp()->reduceHp(Map_Disparos::disparos[id]->getDamage());
                            if (enemigos_sfml[i]->getHp()->getHp() > 0)
                            {
                                enemigos_sfml[i]->setReceive_damage(true);
                            }
                        }
                        colisiona = true;
                    }
                }
            }
        }
        else if(Map_Disparos::disparos[id]->getObjetivo() == Objetivo::player_two) 
        {
            // Colisión con jugador 2
            auto* player = Game_t::getInstance()->getPlayerTwo();
            if(sprtwo->getGlobalBounds().intersects(disparos[id]->getGlobalBounds()) && player->getEstado() != Estado_Personaje::morir) 
            {
                if (player->getReceive_damage() == false)
                {
                    player->getHp()->reduceHp(Map_Disparos::disparos[id]->getDamage());
                    if (player->getHp()->getHp() > 0)
                    {
                        player->setReceive_damage(true);
                    }
                }
                colisiona =  true;
            }
            // Colisión con enemigos
            auto enemigos_sfml = Game_t::getInstance()->getEnemies();
            for(unsigned int i = 0; i < enemigos_sfml.size(); i++) 
            {
                if(enemigos_sfml[i] != nullptr) 
                {
                    if(enemigos[i]->getGlobalBounds().intersects(disparos[id]->getGlobalBounds()) && enemigos_sfml[i]->getEstadoEnemy() != Estado_Personaje::morir)
                    {
                        if (enemigos_sfml[i]->getReceive_damage() == false)
                        {
                            enemigos_sfml[i]->getHp()->reduceHp(Map_Disparos::disparos[id]->getDamage());
                            if (enemigos_sfml[i]->getHp()->getHp() > 0)
                            {
                                enemigos_sfml[i]->setReceive_damage(true);
                            }
                        }
                        colisiona = true;
                    }
                }
            }
        }
        else if (Map_Disparos::disparos[id]->getObjetivo() == Objetivo::both)
        {
            auto* p1 = Game_t::getInstance()->getPlayerOne();
            auto* p2 = Game_t::getInstance()->getPlayerTwo();
            if(sprone->getGlobalBounds().intersects(disparos[id]->getGlobalBounds())) 
            {
                if (p1->getReceive_damage() == false && p1->getEstado() != Estado_Personaje::morir)
                {
                    p1->getHp()->reduceHp(Map_Disparos::disparos[id]->getDamage());
                    if (p1->getHp()->getHp() > 0)
                    {
                        p1->setReceive_damage(true);
                    }
                }
                colisiona =  true;
            }
            else if(sprtwo->getGlobalBounds().intersects(disparos[id]->getGlobalBounds())) 
            {
                if (p2->getReceive_damage() == false && p2->getEstado() != Estado_Personaje::morir)
                {
                    p2->getHp()->reduceHp(Map_Disparos::disparos[id]->getDamage());
                    if (p2->getHp()->getHp() > 0)
                    {
                        p2->setReceive_damage(true);
                    }
                }
                colisiona =  true;
            }
        }
        
    }
    return colisiona;
}

bool SfmlGraphics::checkCollisionDisparo(int i, int j, EntityID_t id) {
    bool colisiona = false;
    if(disparos[id] != nullptr) 
    {
        colisiona = spritessfml[i][j]->getGlobalBounds().intersects(disparos[id]->getGlobalBounds());
    }
    return colisiona;
}


bool SfmlGraphics::checkCollisionKit(int id) {
    if(kit != nullptr) {
        if(id == ID_PLAYER_ONE){
            return sprone->getGlobalBounds().intersects(kit->getGlobalBounds()); 
        }
    
        return sprtwo->getGlobalBounds().intersects(kit->getGlobalBounds());
    }
    return false;
}

bool SfmlGraphics::checkCollisionRespawn(int id) {
    if(respawn_one != nullptr && respawn_two != nullptr) {
        if(id == ID_PLAYER_ONE){
            return sprone->getGlobalBounds().intersects(respawn_one->getGlobalBounds()); 
        }
    
        return sprtwo->getGlobalBounds().intersects(respawn_two->getGlobalBounds());
    }
    return false;
}

std::pair<EntityID_t,bool> SfmlGraphics::checkCollisionPowerUps(int id) {
    if(id == ID_PLAYER_ONE && Game_t::getInstance()->getPlayerOne()->getPowerUp() == nullptr){
        for(auto& pw : powerUps) {
            if(pw.second != nullptr) {
                auto res = std::pair<EntityID_t,bool>(pw.first,sprone->getGlobalBounds().intersects(pw.second->getGlobalBounds()));
                if(res.second) {
                    delete pw.second;
                    pw.second = nullptr;
                    powerUps.erase(pw.first);
                    return res;
                }
            }
        }
    }else if(id == ID_PLAYER_TWO && Game_t::getInstance()->getPlayerTwo()->getPowerUp() == nullptr) {
        for(auto& pw : powerUps) {
            if(pw.second) {
                auto res = std::pair<EntityID_t,bool>(pw.first,sprtwo->getGlobalBounds().intersects(pw.second->getGlobalBounds()));
                if(res.second) {
                    delete pw.second;
                    pw.second = nullptr;
                    powerUps.erase(pw.first);
                    return res;
                }
            }
        }
    }

    return std::pair<EntityID_t,bool>(-1,false);
}

void SfmlGraphics::reset_power_ups() {
    for (size_t i = 0; i < powerUps.size(); i++){
        if(powerUps[i] != nullptr) {
            auto* p = powerUps[i];
            delete powerUps[i];
            p = nullptr;
        }
    }
    powerUps.clear();
}


bool SfmlGraphics::checkCollision(int i, int j, int id) {
    if(spritessfml[i][j] != nullptr) {
        if(id == ID_PLAYER_ONE){
            return spritessfml[i][j]->getGlobalBounds().intersects(sprone->getGlobalBounds());
        }
        return spritessfml[i][j]->getGlobalBounds().intersects(sprtwo->getGlobalBounds());
    }
}

bool SfmlGraphics::checkCollisionSpikes(int id) {
    if(id == ID_PLAYER_ONE){
        for(unsigned int i = 0; i < spikes_2.size(); i++) {
            if(sprone->getGlobalBounds().intersects(spikes_2[i]->getGlobalBounds())){
                return true;
            }
        }
    }else{
        for(unsigned int i = 0; i < spikes_1.size(); i++) {
            if(sprtwo->getGlobalBounds().intersects(spikes_1[i]->getGlobalBounds())){
                return true;
            }
        }
    }
    return false;
}

void SfmlGraphics::attackmele(Player_t* p) {
    if(p->getID() == ID_PLAYER_ONE) 
    {
        // Colisión con Player 2
        auto* p2 = Game_t::getInstance()->getPlayerTwo();
        if(p2->getEstado() != Estado_Personaje::morir && !p2->getReceive_damage() && sprone->getGlobalBounds().intersects(sprtwo->getGlobalBounds()))
        {
            p2->getHp()->reduceHp(p->getArma()->getDamage());
            if (p2->getHp()->getHp() > 0)
            {
                p2->setReceive_damage(true);
            }
        }
        // Colisión con enemigos
        auto enemigos_sfml = Game_t::getInstance()->getEnemies();
        for(unsigned int i = 0; i < enemigos_sfml.size(); i++) 
        {
            if(enemigos_sfml[i] != nullptr) 
            {
                if(enemigos_sfml[i]->getEstadoEnemy() != Estado_Personaje::morir && !enemigos_sfml[i]->getReceive_damage() && sprone->getGlobalBounds().intersects(enemigos[i]->getGlobalBounds()))
                {
                    enemigos_sfml[i]->getHp()->reduceHp(p->getArma()->getDamage());
                    if (enemigos_sfml[i]->getHp()->getHp() > 0)
                    {
                        enemigos_sfml[i]->setReceive_damage(true);
                    }
                }
            }
        }
    }
    else
    {
        // Colisión con Player 1
        auto* p1 = Game_t::getInstance()->getPlayerOne();
        if(sprtwo->getGlobalBounds().intersects(sprone->getGlobalBounds()) && p1->getEstado() != Estado_Personaje::morir && !p1->getReceive_damage()){
            p1->getHp()->reduceHp(p->getArma()->getDamage());
            if (p1->getHp()->getHp() > 0)
            {
                p1->setReceive_damage(true);
            }
        }
        // Colisión con enemigos
        auto enemigos_sfml = Game_t::getInstance()->getEnemies();
        for(unsigned int i = 0; i < enemigos_sfml.size(); i++) 
        {
            if(enemigos_sfml[i] != nullptr) 
            {
                if(enemigos_sfml[i]->getEstadoEnemy() != Estado_Personaje::morir && !enemigos_sfml[i]->getReceive_damage() && sprtwo->getGlobalBounds().intersects(enemigos[i]->getGlobalBounds()))
                {
                    enemigos_sfml[i]->getHp()->reduceHp(p->getArma()->getDamage());
                    if (enemigos_sfml[i]->getHp()->getHp() > 0)
                    {
                        enemigos_sfml[i]->setReceive_damage(true);
                    }
                }
            }
        }
    }
}

// Comprobamos la colision del jugador con el rango del enemigo
bool SfmlGraphics::checkCollisionRange(EntityID_t idPlayer, EntityID_t idEnemy)
{
    bool colisiona = false;
    if(idPlayer == ID_PLAYER_ONE && rangos[idEnemy-1] != NULL && sprone->getGlobalBounds().intersects(rangos[idEnemy-1]->getGlobalBounds())) 
        colisiona = true; 
    else if(idPlayer == ID_PLAYER_TWO && rangos[idEnemy-1] != NULL && sprtwo->getGlobalBounds().intersects(rangos[idEnemy-1]->getGlobalBounds())) 
        colisiona = true; 

    return colisiona;
}

// Comprobamos la colision del jugador con el el enemigo. Solo pursuit (cuando ataca) y patrol
bool SfmlGraphics::checkCollisionEnemyPlayer(EntityID_t idPlayer, EntityID_t idEnemy)
{
    bool colisiona = false;
    if(idPlayer == ID_PLAYER_ONE && enemigos[idEnemy-1] != NULL && sprone->getGlobalBounds().intersects(enemigos[idEnemy-1]->getGlobalBounds())) 
        colisiona = true; 
    else if(idPlayer == ID_PLAYER_TWO && enemigos[idEnemy-1] != NULL && sprtwo->getGlobalBounds().intersects(enemigos[idEnemy-1]->getGlobalBounds())) 
        colisiona = true; 

    return colisiona;
}

void SfmlGraphics::select_frame(sf::Sprite* s,Player_t* p){
    //Game_t::getInstance()->getAnimation()->estados[p->getPersonaje()];
    switch (p->getEstado()){
    case Estado_Personaje::andar :
        
        s->setTextureRect(
            sf::IntRect(
            Game_t::getInstance()->getAnimation()->estados[p->getPersonaje()]->walking_r[p->getSprite()->frame_r]->x,
            Game_t::getInstance()->getAnimation()->estados[p->getPersonaje()]->walking_r[p->getSprite()->frame_r]->y, 
            Game_t::getInstance()->getAnimation()->estados[p->getPersonaje()]->walking_r[p->getSprite()->frame_r]->w,
            Game_t::getInstance()->getAnimation()->estados[p->getPersonaje()]->walking_r[p->getSprite()->frame_r]->h)
        );  

    break;
    
    case Estado_Personaje::atacar:
        s->setTextureRect(
            sf::IntRect(
            Game_t::getInstance()->getAnimation()->estados[p->getPersonaje()]->attacking[p->getSprite()->frame_r]->x,
            Game_t::getInstance()->getAnimation()->estados[p->getPersonaje()]->attacking[p->getSprite()->frame_r]->y, 
            Game_t::getInstance()->getAnimation()->estados[p->getPersonaje()]->attacking[p->getSprite()->frame_r]->w,
            Game_t::getInstance()->getAnimation()->estados[p->getPersonaje()]->attacking[p->getSprite()->frame_r]->h)
        );
    break;

    case Estado_Personaje::morir:
        s->setTextureRect(
            sf::IntRect(
            Game_t::getInstance()->getAnimation()->estados[p->getPersonaje()]->dying[p->getSprite()->frame_r]->x,
            Game_t::getInstance()->getAnimation()->estados[p->getPersonaje()]->dying[p->getSprite()->frame_r]->y, 
            Game_t::getInstance()->getAnimation()->estados[p->getPersonaje()]->dying[p->getSprite()->frame_r]->w,
            Game_t::getInstance()->getAnimation()->estados[p->getPersonaje()]->dying[p->getSprite()->frame_r]->h)
        );
    break;

    case Estado_Personaje::parado:
        s->setTextureRect(
            sf::IntRect(
            Game_t::getInstance()->getAnimation()->estados[p->getPersonaje()]->parado[p->getSprite()->frame_r]->x,
            Game_t::getInstance()->getAnimation()->estados[p->getPersonaje()]->parado[p->getSprite()->frame_r]->y, 
            Game_t::getInstance()->getAnimation()->estados[p->getPersonaje()]->parado[p->getSprite()->frame_r]->w,
            Game_t::getInstance()->getAnimation()->estados[p->getPersonaje()]->parado[p->getSprite()->frame_r]->h)
        );
    break;
    default:
        break;
    }
    
}

void SfmlGraphics::select_frameEnemy(sf::Sprite* s,Enemy* e){
    //Game_t::getInstance()->getAnimation()->estados[p->getPersonaje()];
    switch (e->getEstadoEnemy()){
    case Estado_Personaje::andar :
        
        s->setTextureRect(
            sf::IntRect(
            Game_t::getInstance()->getAnimation()->estados[e->getEnemy()]->walking_r[e->getSprite()->frame_r]->x,
            Game_t::getInstance()->getAnimation()->estados[e->getEnemy()]->walking_r[e->getSprite()->frame_r]->y, 
            Game_t::getInstance()->getAnimation()->estados[e->getEnemy()]->walking_r[e->getSprite()->frame_r]->w,
            Game_t::getInstance()->getAnimation()->estados[e->getEnemy()]->walking_r[e->getSprite()->frame_r]->h)
        );  

    break;
    
    case Estado_Personaje::atacar:
        s->setTextureRect(
            sf::IntRect(
            Game_t::getInstance()->getAnimation()->estados[e->getEnemy()]->attacking[e->getSprite()->frame_r]->x,
            Game_t::getInstance()->getAnimation()->estados[e->getEnemy()]->attacking[e->getSprite()->frame_r]->y, 
            Game_t::getInstance()->getAnimation()->estados[e->getEnemy()]->attacking[e->getSprite()->frame_r]->w,
            Game_t::getInstance()->getAnimation()->estados[e->getEnemy()]->attacking[e->getSprite()->frame_r]->h)
        );
    break;

    case Estado_Personaje::morir:
        s->setTextureRect(
            sf::IntRect(
            Game_t::getInstance()->getAnimation()->estados[e->getEnemy()]->dying[e->getSprite()->frame_r]->x,
            Game_t::getInstance()->getAnimation()->estados[e->getEnemy()]->dying[e->getSprite()->frame_r]->y, 
            Game_t::getInstance()->getAnimation()->estados[e->getEnemy()]->dying[e->getSprite()->frame_r]->w,
            Game_t::getInstance()->getAnimation()->estados[e->getEnemy()]->dying[e->getSprite()->frame_r]->h)
        );
    break;

    case Estado_Personaje::parado:
        s->setTextureRect(
            sf::IntRect(
            Game_t::getInstance()->getAnimation()->estados[e->getEnemy()]->parado[e->getSprite()->frame_r]->x,
            Game_t::getInstance()->getAnimation()->estados[e->getEnemy()]->parado[e->getSprite()->frame_r]->y, 
            Game_t::getInstance()->getAnimation()->estados[e->getEnemy()]->parado[e->getSprite()->frame_r]->w,
            Game_t::getInstance()->getAnimation()->estados[e->getEnemy()]->parado[e->getSprite()->frame_r]->h)
        );
        
    break;
    default:
        break;
    }
    
}

void SfmlGraphics::animate_frame(Sprite_t* s, int id){
    Player_t* pl;
    sf::Sprite* spr;

    if(id == ID_PLAYER_ONE){
        pl = Game_t::getInstance()->getPlayerOne();
        spr = sprone;
    }
    else
    {
        pl = Game_t::getInstance()->getPlayerTwo();
        spr = sprtwo;
    }

    switch (pl->getEstado()){
    case Estado_Personaje::andar :
        if(pl->getTimeAnimation() == 0.f) 
        {
            pl->updateTimeAnimation();
        }
        if(s->frame_r !=  Game_t::getInstance()->getAnimation()->estados[pl->getPersonaje()]->walking_r.size()-1 && getTimeElapsed() >= pl->getTimeAnimation())
        {
            s->frame_r++;
            pl->updateTimeAnimation();
        }
        else if(s->frame_r ==  Game_t::getInstance()->getAnimation()->estados[pl->getPersonaje()]->walking_r.size()-1 && getTimeElapsed() >= pl->getTimeAnimation())
        {
            s->frame_r = 0;
            pl->setTimeAnimation(0.f);
        }
    break;

    case Estado_Personaje::atacar :
        if(pl->getTimeAnimation() == 0.f) 
        {
            pl->updateTimeAnimation();
        }
        if(s->frame_r !=  Game_t::getInstance()->getAnimation()->estados[pl->getPersonaje()]->attacking.size()-1 && getTimeElapsed() >= pl->getTimeAnimation())
        {
            s->frame_r++;
            pl->updateTimeAnimation();
        }
        else if(s->frame_r ==  Game_t::getInstance()->getAnimation()->estados[pl->getPersonaje()]->attacking.size()-1 && getTimeElapsed() >= pl->getTimeAnimation())
        {
            pl->setEstado_after_dead(Estado_Personaje::parado);
            s->frame_r = 0;
            pl->setTimeAnimation(0.f);
        }
    break;

    case Estado_Personaje::morir :
        if(pl->getTimeAnimation() == 0.f) 
        {
            pl->updateTimeAnimation();
        }
        if(s->frame_r !=  Game_t::getInstance()->getAnimation()->estados[pl->getPersonaje()]->dying.size()-1 && getTimeElapsed() >= pl->getTimeAnimation())
        {
            s->frame_r++;
            pl->updateTimeAnimation();
        }
        else if(s->frame_r ==  Game_t::getInstance()->getAnimation()->estados[pl->getPersonaje()]->dying.size()-1 && getTimeElapsed() >= pl->getTimeAnimation())
        {
            pl->setEstado_after_dead(Estado_Personaje::parado);
            pl->getSprite()->getPhysics()->respawn(pl->getID());
            s->frame_r = 0;
            pl->setTimeAnimation(0.f);
        }
    break;

    case Estado_Personaje::parado :
        if(pl->getTimeAnimation() == 0.f) 
        {
            pl->updateTimeAnimation();
        }
        if(s->frame_r !=  Game_t::getInstance()->getAnimation()->estados[pl->getPersonaje()]->parado.size()-1 && getTimeElapsed() >= pl->getTimeAnimation())
        {
            s->frame_r++;
            pl->updateTimeAnimation();
        }
        else if(s->frame_r ==  Game_t::getInstance()->getAnimation()->estados[pl->getPersonaje()]->parado.size()-1 && getTimeElapsed() >= pl->getTimeAnimation())
        {
            s->frame_r = 0;
            pl->setTimeAnimation(0.f);
        }
    break;
    
    default:
        break;
    }
    select_frame(spr,pl);
}

void SfmlGraphics::animatedEnemies(Enemy* enemigo){
    
    switch (enemigo->getEstadoEnemy()){
        case Estado_Personaje::andar :
            if(enemigo->getTimeAnimation() == 0.f) 
            {
                enemigo->updateTimeAnimation();
            }
            if(enemigo->getSprite()->frame_r !=  Game_t::getInstance()->getAnimation()->estados[enemigo->getEnemy()]->walking_r.size()-1 && getTimeElapsed() >= enemigo->getTimeAnimation())
            {
                enemigo->getSprite()->frame_r++;
                enemigo->updateTimeAnimation();
            }
            else if(enemigo->getSprite()->frame_r ==  Game_t::getInstance()->getAnimation()->estados[enemigo->getEnemy()]->walking_r.size()-1 && getTimeElapsed() >= enemigo->getTimeAnimation())
            {
                enemigo->getSprite()->frame_r = 0;
                enemigo->setTimeAnimation(0.f);
            }
        break;

        case Estado_Personaje::atacar :
            if(enemigo->getTimeAnimation() == 0.f) 
            {
                enemigo->updateTimeAnimation();
            }
            if(enemigo->getSprite()->frame_r !=  Game_t::getInstance()->getAnimation()->estados[enemigo->getEnemy()]->attacking.size()-1 && getTimeElapsed() >= enemigo->getTimeAnimation())
            {
                enemigo->getSprite()->frame_r++;
                enemigo->updateTimeAnimation();
            }
            else if(enemigo->getSprite()->frame_r ==  Game_t::getInstance()->getAnimation()->estados[enemigo->getEnemy()]->attacking.size()-1 && getTimeElapsed() >= enemigo->getTimeAnimation())
            {
                enemigo->getSprite()->frame_r = 0;
                enemigo->setEstado_after_dead(Estado_Personaje::parado);
                enemigo->setTimeAnimation(0.f);
            }
        break;

        case Estado_Personaje::morir :
            if(enemigo->getTimeAnimation() == 0.f) 
            {
                enemigo->updateTimeAnimation();
            }
            if(enemigo->getSprite()->frame_r !=  Game_t::getInstance()->getAnimation()->estados[enemigo->getEnemy()]->dying.size()-1 && getTimeElapsed() >= enemigo->getTimeAnimation())
            {
                enemigo->getSprite()->frame_r++;
                enemigo->updateTimeAnimation();
                if(enemigo->getSprite()->frame_r ==  Game_t::getInstance()->getAnimation()->estados[enemigo->getEnemy()]->dying.size()-1) 
                {
                    enemigo->updateTimeRespawn();
                    //enemigo->getSprite()->getPhysics()->x = -100.0;
                    //enemigo->getSprite()->getPhysics()->y = -100.0;
                }
            }
            else if(enemigo->getSprite()->frame_r ==  Game_t::getInstance()->getAnimation()->estados[enemigo->getEnemy()]->dying.size()-1 && getTimeElapsed() >= enemigo->getTimeAnimation() && getTimeElapsed() >= enemigo->getTimeRespawn())
            {
                enemigo->setEstado_after_dead(Estado_Personaje::parado);
                enemigo->getSprite()->getPhysics()->respawnEnemy(enemigo->getID());
                enemigo->getSprite()->frame_r = 0;
                enemigo->setTimeAnimation(0.f);
            }
        break;

        case Estado_Personaje::parado :
            if(enemigo->getTimeAnimation() == 0.f) 
            {
                enemigo->updateTimeAnimation();
            }
            if(enemigo->getSprite()->frame_r !=  Game_t::getInstance()->getAnimation()->estados[enemigo->getEnemy()]->parado.size()-1 && getTimeElapsed() >= enemigo->getTimeAnimation())
            {
                enemigo->getSprite()->frame_r++;
                enemigo->updateTimeAnimation();
            }
            else if(enemigo->getSprite()->frame_r ==  Game_t::getInstance()->getAnimation()->estados[enemigo->getEnemy()]->parado.size()-1 && getTimeElapsed() >= enemigo->getTimeAnimation())
            {
                enemigo->getSprite()->frame_r = 0;
                enemigo->setTimeAnimation(0.f);
            }
        break;
        
        default:
            break;
        }
        select_frameEnemy(enemigos[enemigo->getID()-1],enemigo);
    
}

void SfmlGraphics::revertAnimation(Player_t* p){
    if(p->getID() == ID_PLAYER_ONE){
        sprone->setScale(
                p->getDireccion()->direccionAnimacion[p->getDireccion()->dirAn], 1);
    }else{
        sprtwo->setScale(
                p->getDireccion()->direccionAnimacion[p->getDireccion()->dirAn], 1); 
    }
}

void SfmlGraphics::createHUD() {
    auto* get_hud = Game_t::getInstance()->getHud();
    hud = new sf::Texture();
    if(hud->loadFromFile(get_hud->getRoute())){
        //Corazones
        brawl.loadFromFile("resources/fonts/Brawl/brawl.ttf");
        j1.setFont(brawl);
        j1.setString("J1");
        j1.setColor(sf::Color(0,0,0));
        j1.setPosition(get_hud->getHud_items()["J1"].first,get_hud->getHud_items()["J1"].second-20);

        j2.setFont(brawl);
        j2.setString("J2");
        j2.setColor(sf::Color(0,0,0));
        j2.setPosition(get_hud->getHud_items()["J2"].first,get_hud->getHud_items()["J2"].second-20);

        int pos = 0;
        for(auto& hearts_one : get_hud->life_pl_one){
            sf::Sprite* s = new sf::Sprite(*hud);
            s->setOrigin(std::get<0>(hearts_one.second)/2,
            std::get<1>(hearts_one.second)/2);
            s->setTextureRect(
                sf::IntRect(
                    std::get<2>(hearts_one.second),
                    std::get<3>(hearts_one.second),
                    std::get<0>(hearts_one.second),
                    std::get<1>(hearts_one.second)
                )
            );
            s->setPosition(get_hud->getHud_items()["life_1"].first + pos, get_hud->getHud_items()["life_1"].second);
            pos+= 30;
            hud_one.emplace(hearts_one.first, s);
        }

        pos = 0;
        for(auto& hearts_two : get_hud->life_pl_two) {
            sf::Sprite* s = new sf::Sprite(*hud);
            s->setOrigin(std::get<0>(hearts_two.second)/2,
            std::get<1>(hearts_two.second)/2);
            s->setTextureRect(
                sf::IntRect(
                    std::get<2>(hearts_two.second),
                    std::get<3>(hearts_two.second),
                    std::get<0>(hearts_two.second),
                    std::get<1>(hearts_two.second)
                )
            );
            s->setPosition(get_hud->getHud_items()["life_2"].first + pos, get_hud->getHud_items()["life_2"].second);
            pos+= 30;
            hud_two.emplace(hearts_two.first, s);
        }

        sf::Sprite* s = new sf::Sprite(*hud);
        //Powerup hud
        
        s->setOrigin(std::get<0>(get_hud->posiciones_[0])/2,std::get<1>(get_hud->posiciones_[0])/2);
        s->setTextureRect(
            sf::IntRect(
                std::get<2>(get_hud->posiciones_[0]),
                std::get<3>(get_hud->posiciones_[0]),
                std::get<0>(get_hud->posiciones_[0]),
                std::get<1>(get_hud->posiciones_[0])
            )
        );
        s->setPosition(get_hud->getHud_items()["PowerUp_1"].first, get_hud->getHud_items()["PowerUp_1"].second);
        s->setScale(1.4,1.4);
        hud_items.push_back(s);

        s = new sf::Sprite(*hud);

        s->setOrigin(std::get<0>(get_hud->posiciones_[0])/2,std::get<1>(get_hud->posiciones_[0])/2);
        s->setTextureRect(
            sf::IntRect(
                std::get<2>(get_hud->posiciones_[0]),
                std::get<3>(get_hud->posiciones_[0]),
                std::get<0>(get_hud->posiciones_[0]),
                std::get<1>(get_hud->posiciones_[0])
            )
        );
        s->setPosition(get_hud->getHud_items()["PowerUp_2"].first, get_hud->getHud_items()["PowerUp_2"].second);
        s->setScale(1.4,1.4);
        hud_items.push_back(s);

        ronda.setFont(brawl);
        ronda.setString(std::to_string(Game_t::getInstance()->getRonda()->getPunuaje(0)) + " - " + std::to_string( Game_t::getInstance()->getRonda()->getPunuaje(1)));
        ronda.setScale(1.1,1.1);
        ronda.setPosition(get_hud->getHud_items()["Cronometro"].first,get_hud->getHud_items()["Cronometro"].second-10);
    }
}

void SfmlGraphics::updateHUD() {
    Hud* hud_ = Game_t::getInstance()->getHud();
    //std::cout << hud_one.size() << std::endl;
    for(unsigned int i = 0; i < hud_one.size(); i++) {
        if(hud_one[i] != nullptr){

            hud_one[i]->setTextureRect(
                sf::IntRect(
                    std::get<2>(hud_->life_pl_one.at(i)),
                    std::get<3>(hud_->life_pl_one.at(i)),
                    std::get<0>(hud_->life_pl_one.at(i)),
                    std::get<1>(hud_->life_pl_one.at(i))
                )
            );
        }
    }

    for(unsigned int i = 0; i < hud_two.size(); i++) {
        if(hud_two[i] != nullptr){
            hud_two[i]->setTextureRect(
                sf::IntRect(
                    std::get<2>(hud_->life_pl_two.at(i)),
                    std::get<3>(hud_->life_pl_two.at(i)),
                    std::get<0>(hud_->life_pl_two.at(i)),
                    std::get<1>(hud_->life_pl_two.at(i))
                )
            );
        }
    }
    ronda.setString(std::to_string(Game_t::getInstance()->getRonda()->getPunuaje(0)) + " - " + std::to_string( Game_t::getInstance()->getRonda()->getPunuaje(1)));

    auto* mapa = Game_t::getInstance()->getMap();
    if(mini_kit == nullptr) {
        mini_kit = new sf::Sprite(*objects);
        mini_kit->setTextureRect(
                sf::IntRect(34 * 2
                , 0 , 
                mapa->getKit()->getWidth(), 
                mapa->getKit()->getHeight())
        );
    }
    mini_kit->setPosition(5000,5000);
    mini_kit->setScale(1.6f,1.6f);
    if(Game_t::getInstance()->getPlayerOne()->getKit() != nullptr) {
        mini_kit->setPosition(hud_->getHud_items()["life_1"].first + 170, hud_->getHud_items()["life_1"].second-15);
    }

    if(Game_t::getInstance()->getPlayerTwo()->getKit() != nullptr) {
        mini_kit->setPosition(hud_->getHud_items()["life_2"].first + 170, hud_->getHud_items()["life_2"].second-15);
    }

    if(Game_t::getInstance()->getPlayerOne()->getPowerUp() != nullptr) {
        if(pw1 == nullptr){
            pw1 = new sf::Sprite(*hud);
        }
        if(count == -1) {
            count = getTimeElapsed()+3;
        }
        
        if(count <= getTimeElapsed()) {
            int pw = hud_->powerUps_hud[Game_t::getInstance()->getPlayerOne()->getPowerUp()->getCategory()];
            pw1->setOrigin(std::get<0>(hud_->posiciones_[pw])/2, std::get<1>(hud_->posiciones_[pw])/2);
            pw1->setTextureRect(
                sf::IntRect(
                    std::get<2>(hud_->posiciones_[pw]),
                    std::get<3>(hud_->posiciones_[pw]),
                    std::get<0>(hud_->posiciones_[pw]),
                    std::get<1>(hud_->posiciones_[pw])
                )
            );
            
        }else{
            if(pospw_1 >= hud_->powerUps_hud.size()){
                pospw_1 = 0;
            }
            pw1->setOrigin(std::get<0>(hud_->posiciones_[pospw_1])/2, std::get<1>(hud_->posiciones_[pospw_1])/2);
            pw1->setTextureRect(
            sf::IntRect(
                std::get<2>(hud_->posiciones_[pospw_1]),
                std::get<3>(hud_->posiciones_[pospw_1]),
                std::get<0>(hud_->posiciones_[pospw_1]),
                std::get<1>(hud_->posiciones_[pospw_1])
                )
            );
            pospw_1++;
        }

        pw1->setPosition(hud_->getHud_items()["PowerUp_1"].first, hud_->getHud_items()["PowerUp_1"].second);
    }else{
        count = -1;
        delete pw1;
        pw1 = nullptr;
    }


    if(Game_t::getInstance()->getPlayerTwo()->getPowerUp() != nullptr) {
        if(pw2 == nullptr){
            pw2 = new sf::Sprite(*hud);
        }
        if(count_ == -1) {
            count_ = getTimeElapsed()+3;
        }
        
        if(count_ <= getTimeElapsed()) {
            int pw = hud_->powerUps_hud[Game_t::getInstance()->getPlayerTwo()->getPowerUp()->getCategory()];
            pw2->setOrigin(std::get<0>(hud_->posiciones_[pw])/2, std::get<1>(hud_->posiciones_[pw])/2);
            pw2->setTextureRect(
                sf::IntRect(
                    std::get<2>(hud_->posiciones_[pw]),
                    std::get<3>(hud_->posiciones_[pw]),
                    std::get<0>(hud_->posiciones_[pw]),
                    std::get<1>(hud_->posiciones_[pw])
                )
            );
            
        }else{
            if(pospw_2 >= hud_->powerUps_hud.size()) {
                pospw_2 = 0;
            }
            pw2->setOrigin(std::get<0>(hud_->posiciones_[pospw_2])/2, std::get<1>(hud_->posiciones_[pospw_2])/2);
            pw2->setTextureRect(
            sf::IntRect(
                std::get<2>(hud_->posiciones_[pospw_2]),
                std::get<3>(hud_->posiciones_[pospw_2]),
                std::get<0>(hud_->posiciones_[pospw_2]),
                std::get<1>(hud_->posiciones_[pospw_2])
                )
            );
            pospw_2++;
        }

        pw2->setPosition(hud_->getHud_items()["PowerUp_2"].first, hud_->getHud_items()["PowerUp_2"].second);
    }else{
        count_ = -1;
        delete pw2;
        pw2 = nullptr;
    }
}

//InitMenu

void SfmlGraphics::initMenu() {
    //std::cout<<"Entra metodo\n";
    menu = new Menu(widthScreen,heightScreen,0);
}

void SfmlGraphics::initMenuJugar(){
    mPlay = new MenuJugar(widthScreen, heightScreen, 0);
}

void SfmlGraphics :: initMenuControles(){
    mCont = new MenuControles(widthScreen, heightScreen);
}

void SfmlGraphics::getInputMenu() {
    sf::Event event;
    while(window->pollEvent(event)){
        switch(event.type){
        case sf::Event::KeyReleased:
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                menu->MoveUp();
                break;

            case sf::Keyboard::Down:
                menu->MoveDown();
                break;

            case sf::Keyboard::Return:
                switch (menu->GetItemSelected()){

                case 0:
                    menu->getSound()->play("click");
                    Game_t::getInstance()->setState(State_t::MPLAY);
                    break;

                case 1:
                    //std::cout<<"Controles se ha presionado" << std::endl;
                    Game_t::getInstance()->setState(State_t::CONTROLS);
                    break;

                case 2:
                    window->close();
                    break;
                }
                break;
            }
            break;

        case sf::Event::Closed:
            window->close();
            break;
        }
    }
}

void SfmlGraphics::getInputMenuJugar(){
    sf::Event event;  
    while(window->pollEvent(event)){
        switch(event.type){
        case sf::Event::KeyReleased:
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                mPlay->MoveUp();
                break;

            case sf::Keyboard::Down:
                mPlay->MoveDown();
                break;
            case sf::Keyboard::A:
                if(mPlay->GetItemSelected() == 0){
                    mPlay->cambiarSprite(0, aux);
                    aux++;
                }
                break;
            case sf::Keyboard::D:
                if(mPlay->GetItemSelected() == 0){
                    mPlay->cambiarSprite(0, aux);
                    aux++;
                }
                break;
            case sf::Keyboard::Left:
                if(mPlay->GetItemSelected() == 0){
                    mPlay->cambiarSprite(1, aux2);
                    aux2++;
                }
                if(mPlay->GetItemSelected() == 1){
                    mPlay->elegirMapa(auxColor);
                    mPlay->move(auxColor);
                    auxColor++;
                }
                break;
            case sf::Keyboard::Right:
                if(mPlay->GetItemSelected() == 0){
                    mPlay->cambiarSprite(1, aux2);
                    aux2++;
                }
                if(mPlay->GetItemSelected() == 1){
                    mPlay->elegirMapa(auxColor);
                    mPlay->move(auxColor);
                    auxColor++;
                }
                break;
            case sf::Keyboard::Return:
                if(comprobacion)
                switch (mPlay->GetItemSelected()){
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    mPlay->getSound()->play("click");
                    Game_t::getInstance()->setState(State_t::INGAME);
                    break;
                case 3:
                    Game_t::getInstance()->setState(State_t::INIT);
                    break;
                }
                break;
            }
            break;

        case sf::Event::Closed:
            window->close();
            break;
        }
    }
}

void SfmlGraphics::getInputMenuControles(){
 sf::Event event;  
    while(window->pollEvent(event)){
        switch(event.type){
        case sf::Event::KeyReleased:
            switch (event.key.code)
            {
            case sf::Keyboard::Return:
                if(comprobacion)
                switch (mCont->getItemSelected()){
                case 0:
                    Game_t::getInstance()->setState(State_t::INIT);
                    break;
                }
                break;
            }
            break;

        case sf::Event::Closed:
            window->close();
            break;
        }
    }
}


void SfmlGraphics::updateMenu() {
    //std::cout<<"Entra main\n";
    window->clear();
    menu->draw(*window);
    window->display();
}

void SfmlGraphics::updateMenuJugar() {
    window->clear();
    mPlay->draw(*window);
    window->display();
}

void SfmlGraphics::updateMenuControles(){
    //std::cout<<"ENTRA CONT\n";
    window->clear();
    mCont->draw(*window);
    window->display();
}

//Game
void SfmlGraphics::initGame(){

}
void SfmlGraphics::getInputGame() {
    sf::Event event;
    while(window->pollEvent(event)){
        switch(event.type){
        case sf::Event::KeyReleased:
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                window->close();
                break;
            }
            break;

        case sf::Event::Closed:
            window->close();
            break;
        }
    }
}
void SfmlGraphics::updateGame(){

    auto* mapa = Game_t::getInstance()->getMap();
    Player_t* playerone = Game_t::getInstance()->getPlayerOne();
    Player_t* playertwo = Game_t::getInstance()->getPlayerTwo();

    window->clear();

    window->draw(*sprBackground);

    for(unsigned int i = 0; i < spritessfml.size(); i++){
        for(unsigned int j = 0; j < spritessfml[i].size();j++){
            if(spritessfml[i][j] != nullptr && mapa->getMatrizMapa()[i][j]->getVisible() == State_v::visible) {
                window->draw(*spritessfml[i][j]);
            }
        }
    } 

    for(unsigned int i = 0; i < enemigos.size(); i++) {
        if(enemigos[i] != nullptr) {
            window->draw(*enemigos[i]);
        }
    }

    /*for(unsigned int i = 0; i < rangos.size(); i++) {
        if(rangos[i] != nullptr) {
            window->draw(*rangos[i]);
        }
    }*/

    for(unsigned int i = 0; i < hud_items.size(); i++) {
        if(hud_items[i] != nullptr) {
            window->draw(*hud_items[i]);
        }
    }

    for(unsigned int i = 0; i < powerUps.size(); i++) {
        if(powerUps[i] != nullptr) {
            window->draw(*powerUps[i]);
        }
    }

    for(unsigned int i = 0; i < spikes_1.size(); i++) {
        if(spikes_1[i] != nullptr) {
            window->draw(*spikes_1[i]);
        }
    }

    for(unsigned int i = 0; i < spikes_2.size(); i++) {
        if(spikes_2[i] != nullptr) {
            window->draw(*spikes_2[i]);
        }
    }
    
    for(const auto &n : disparos){
        if(n.second != nullptr){
            window->draw(*n.second);
        }
    }

    /*sf::CircleShape shape(5);
    shape.setFillColor(sf::Color(150, 50, 250));
    shape.setPosition(
        playerone->getSprite()->getPhysics()->x,
        playerone->getSprite()->getPhysics()->y
    );*/

    if(kit != nullptr) {
        kit->setPosition(
            mapa->getKit()->getPhysics()->x,
            mapa->getKit()->getPhysics()->y
        );
    }

    if(mapa->getKit()->getVisible() == State_v::visible){
        if(kit != nullptr) {
            window->draw(*kit);
        }
    }

    window->draw(*sprone);
    window->draw(*sprtwo);
    
    /*shape.setPosition(
        sprone->getPosition().x,
        sprone->getPosition().y
    );*/

    //window->draw(shape);
    if(respawn_one != nullptr && respawn_two != nullptr){
        window->draw(*respawn_one);
        window->draw(*respawn_two);
    }

    if(!Game_t::getInstance()->getGameStart()){
        transparencia.setSize(sf::Vector2f(widthScreen,heightScreen));
        transparencia.setPosition(sf::Vector2f(0,0));
        transparencia.setFillColor(sf::Color(15,19,21,150));
        window->draw(transparencia);
    }

    if( Game_t::getInstance()->getTemporizador() != nullptr && Game_t::getInstance()->getTemporizador()->still_time_to_process()) {
        window->draw(textoTempo);
    }
    
    //camara();

    window->draw(j1);
    window->draw(j2);
    if(pw1 != nullptr) {
        window->draw(*pw1);
    }
    if(pw2 != nullptr) {
        window->draw(*pw2);
    }
    if(mini_kit != nullptr) {
        window->draw(*mini_kit);
    }
    window->draw(ronda);

    for(auto& ho : hud_one) {
        if(ho.second != nullptr) {
            window->draw(*ho.second);
        }
    }

    for(auto& ht : hud_two) {
        if(ht.second != nullptr) {
            window->draw(*ht.second);
        }
    }

    //renderHUD.clear();
    //renderHUD.setView(vistaHUD);
    sf::RectangleShape rectangulo;

    rectangulo.setSize({1500, 1000});
    rectangulo.setFillColor(sf::Color(255,204,153));
    //renderHUD.draw(rectangulo);


    //HUD
    //j1.setScale(0.07, 20);
    //j1.setPosition(1, 200);
    //j2.setScale(0.07, 20);
    //j2.setPosition(75, 200);
    //renderHUD.draw(j1);
    //renderHUD.draw(j2);

    //for(unsigned int i = 0; i < hud_items.size(); i++) {
    //    if(hud_items[i] != nullptr) {
    //        hud_items[i]->setScale(0.08, 20);
    //        hud_items[i]->setPosition(28, 550);
    //        renderHUD.draw(*hud_items[i]);
//
    //        hud_items[i]->setPosition(49, 550);
    //        renderHUD.draw(*hud_items[i]);
//
    //    }
    //}


    //if(pw1 != nullptr) {
    //    pw1->setScale(0.097, 20);
    //    pw1->setPosition(28, 550);
    //    renderHUD.draw(*pw1);
    //}

    //if(pw2 != nullptr) {
    //    pw2->setScale(0.097, 20);
    //    pw2->setPosition(49, 550);
    //    renderHUD.draw(*pw2);
    //}

    //ronda.setColor(sf::Color(0,0,0));
    //ronda.setScale(0.12, 20);
    //ronda.setPosition(34, 200);
    //renderHUD.draw(ronda);


    //int cont=1;
    //for(auto& ho : hud_one) {
    //    if(ho.second != nullptr) {
    //        ho.second->setPosition(3+4*cont,600);
    //        ho.second ->setScale(0.097, 20);
    //        renderHUD.draw(*ho.second);
    //        cont++;
    //    }
    //}
//
    //int cont2=1;
    //for(auto& ht : hud_two) {
    //    if(ht.second != nullptr) {
    //        ht.second->setScale(0.097,20);
    //        ht.second->setPosition(50+4*cont2,600);
    //        renderHUD.draw(*ht.second);
    //        cont2++;
    //    }
    //}

   
    //renderHUD.display();
    //header.setTexture(renderHUD.getTexture());
    
    //header.setScale(0.5, 0.5);
    window->draw(header);
    window->setView(vista);
    window->display();

}

std::tuple<int,int,int,int> SfmlGraphics::setColorPlayer(int idPlayer, std::tuple<int,int,int,int> color) 
{
    std::tuple<int,int,int,int> c;
    if(idPlayer == ID_PLAYER_ONE) 
    {
        c = std::tuple<int,int,int,int>(sprone->getColor().r,sprone->getColor().g,sprone->getColor().b,sprone->getColor().a);
        sprone->setColor(sf::Color(std::get<0>(color), std::get<1>(color), std::get<2>(color), std::get<3>(color)));
    }
    else if(idPlayer == ID_PLAYER_TWO) 
    {
        c = std::tuple<int,int,int,int>(sprtwo->getColor().r,sprtwo->getColor().g,sprtwo->getColor().b,sprtwo->getColor().a);
        sprtwo->setColor(sf::Color(std::get<0>(color), std::get<1>(color), std::get<2>(color), std::get<3>(color)));
    }
    return c;
}

std::tuple<int,int,int,int> SfmlGraphics::setColorEnemy(int idEnemy, std::tuple<int,int,int,int> color) 
{
    std::tuple<int,int,int,int> c;
    if(enemigos[idEnemy-1]) 
    {
        c = std::tuple<int,int,int,int>(enemigos[idEnemy-1]->getColor().r,enemigos[idEnemy-1]->getColor().g,enemigos[idEnemy-1]->getColor().b,enemigos[idEnemy-1]->getColor().a);
        enemigos[idEnemy-1]->setColor(sf::Color(std::get<0>(color), std::get<1>(color), std::get<2>(color), std::get<3>(color)));
    }
    return c;
}

//Controlls


void SfmlGraphics::camara(){
    Player_t* playerone = Game_t::getInstance()->getPlayerOne();
    Player_t* playertwo = Game_t::getInstance()->getPlayerTwo();

    int posx1 = playerone->getSprite()->getPhysics()->x;
    int posy1 = playerone->getSprite()->getPhysics()->y;
    int posx2 = playertwo->getSprite()->getPhysics()->x;
    int posy2 = playertwo->getSprite()->getPhysics()->y;

    distanciAnterior = distanciActual;
    distanciActual = sqrt(pow(posx2-posx1, 2) + pow(posy2-posy1, 2))+50;

    float distancia = distanciActual/widthScreen;

    if(!(distancia>1 && vista.getSize().x >=widthScreen)){
        if(distancia<0.996 && vista.getSize().x > widthScreen/2){
            
            distancia = 0.996;

        }else if(distancia<1){
            
            distancia = 1;
    }

    int puntoMediox=0;
    int puntoMedioy=0;

    puntoMediox=(posx2+posx1)/2;
    puntoMedioy=(posy2+posy1)/2;


    /*//Izquierda
    if(puntoMediox<widthScreen/2.7){
        puntoMediox = widthScreen/2.7;
    }

    //Derecha
    if(puntoMediox>widthScreen/1.55){
        puntoMediox = widthScreen/1.55;
    }

    //Arriba
    if(puntoMedioy<heightScreen/2.5){
        puntoMedioy = heightScreen/2.5;
    }

    //Abajo
    if(puntoMedioy > heightScreen/1.55){
        puntoMedioy = heightScreen/1.55;
    }*/

    vista.setCenter(puntoMediox, puntoMedioy);


    if(vista.getSize().x > widthScreen && distancia>1){
        distancia = 1;
    }

    if(distanciActual!=distanciAnterior){
        if(distanciAnterior-distanciActual<=0 && vista.getSize().x <= widthScreen){
            vista.zoom(1.004);


        }else if(distanciActual<distanciAnterior){
            vista.zoom(distancia);

        }
    }

    if(distanciAnterior==0){
        vista.zoom(1);
    }

    if(distanciActual-distanciAnterior>300 && distanciAnterior!=0 && vista.getSize().x < widthScreen*0.7){
        vista.zoom(1.7);
    }
    } 


}