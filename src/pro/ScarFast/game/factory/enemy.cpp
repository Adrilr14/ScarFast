#include "enemy.hpp"
#include "../sys/ia.hpp"
#include "player.hpp"
#include "disparo.hpp"
#include "../../facade/ControllerMan.hpp"
#include "../../facade/Controller.hpp"
#include "../sys/direction.hpp"

#define inmunity_time 0.5f
#define frameTime 0.05f
#define respawn 10.f

// Constructores
Enemy::Enemy(Hp_t* h, int d, Sprite_t *sp, IA *c) : hp(h), damage(d), spEnemy(sp), comportamiento(c), tipoMagia (0), cadenciaDisparo(0.f), posInicial(std::pair<float,float>(sp->getPhysics()->x ,sp->getPhysics()->y)) {}

Enemy::Enemy(Hp_t* h, int d, Sprite_t *sp, IA *c, int tm, float cadencia) : hp(h), damage(d), spEnemy(sp), comportamiento(c), tipoMagia (tm), cadenciaDisparo(cadencia), posInicial(std::pair<float,float>(sp->getPhysics()->x ,sp->getPhysics()->y)) {}

// Destructor
Enemy::~Enemy() {}

// Movimiento del enemigo patrol
void Enemy::moveEnemyPatrol() 
{
    if (comportamiento->getTipoIA() == TipoIA::patrol  && Estado_Personaje::morir != estado)
    {
        // Se mueve de una posición a otra del vector de posiciones 

        // Guardamos las posiciones x e y del enemigo y del vector de patron (se usan enteros para evitar comparaciones muy exactass que no sucedan)
        int posEnemyX = spEnemy->getPhysics()->x;
        int posEnemyY = spEnemy->getPhysics()->y;
        int posPatrolX = comportamiento->getPatrol()[patrolPosition].first;
        int posPatrolY = comportamiento->getPatrol()[patrolPosition].second;

        //std::cout << "Posicion enemigo X = " << posEnemyX << "; Posicion enemigo Y = " << posEnemyY << std::endl;
        //std::cout << "Posicion patrulla X = " << posPatrolX << "; Posicion patrulla Y = " << posPatrolY << std::endl;  

        // Si estamos en la posición del la patrulla actual sumamos 1 a patrolPosition (sin que se pase del size)
        if(posEnemyX == posPatrolX && posEnemyY == posPatrolY)
        {
            patrolPosition++;
            if(patrolPosition >= comportamiento->getPatrol().size()) patrolPosition = 0;
        }

        // Comparamos las posiciones para saber hacia donde se tiene que mover el enemigo
        if(posEnemyX < posPatrolX)
        {
            spEnemy->getPhysics()->x += spEnemy->getPhysics()->velx * ControllerMan::instancia().controller().getDeltaTime();
            if(spEnemy->getPhysics()->x > posPatrolX) {spEnemy->getPhysics()->x = posPatrolX;}
            this->setEstado(Estado_Personaje::andar);
        } 
        else if(posEnemyX > posPatrolX)
        {
            spEnemy->getPhysics()->x -= spEnemy->getPhysics()->velx * ControllerMan::instancia().controller().getDeltaTime();
            if(spEnemy->getPhysics()->x < posPatrolX) {spEnemy->getPhysics()->x = posPatrolX;}
            this->setEstado(Estado_Personaje::andar);
        } 
        if(posEnemyY < posPatrolY)
        {
            spEnemy->getPhysics()->y += spEnemy->getPhysics()->vely * ControllerMan::instancia().controller().getDeltaTime();
            if(spEnemy->getPhysics()->y > posPatrolY) {spEnemy->getPhysics()->y = posPatrolY;}
            this->setEstado(Estado_Personaje::andar);
        } 
        else if(posEnemyY > posPatrolY)
        {
           spEnemy->getPhysics()->y -= spEnemy->getPhysics()->vely * ControllerMan::instancia().controller().getDeltaTime();
           if(spEnemy->getPhysics()->y < posPatrolY){
                spEnemy->getPhysics()->y = posPatrolY;
            }
            this->setEstado(Estado_Personaje::andar);
        }
    }
}

// Movimiento del enemigo pursuit
void Enemy::moveEnemyPursuit(Player_t *pl, bool colisiona) 
{   
    if (comportamiento->getTipoIA() == TipoIA::pursuit)
    {
        // Si el jugador colisiona con el rango que tiene va a hacia él para atacarle
        // Guardamos las posiciones x e y del enemigo (se usan enteros para evitar comparaciones muy exactass que no sucedan)
        int posEnemyX = spEnemy->getPhysics()->x;
        int posEnemyY = spEnemy->getPhysics()->y;
        if(colisiona && Estado_Personaje::morir != estado){
            // Guardamos las posiciones x e y del player (se usan enteros para evitar comparaciones muy exactass que no sucedan)
            int posPlayerX = pl->getSprite()->getPhysics()->x;
            int posPlayerY = pl->getSprite()->getPhysics()->y;
            
            if(posEnemyX > posPlayerX) {
                spEnemy->getPhysics()->x -= spEnemy->getPhysics()->velx * ControllerMan::instancia().controller().getDeltaTime();
                if(spEnemy->getPhysics()->x < posPlayerX) {spEnemy->getPhysics()->x = posPlayerX;}
                if(estado != Estado_Personaje::atacar) estado = Estado_Personaje::andar;
            }
            else if(posEnemyX < posPlayerX) {
                spEnemy->getPhysics()->x += spEnemy->getPhysics()->velx * ControllerMan::instancia().controller().getDeltaTime();
                if(spEnemy->getPhysics()->x > posPlayerX) {spEnemy->getPhysics()->x = posPlayerX;}
                if(estado != Estado_Personaje::atacar) estado = Estado_Personaje::andar;
            } 
            if(posEnemyY > posPlayerY) {
                spEnemy->getPhysics()->y -= spEnemy->getPhysics()->vely * ControllerMan::instancia().controller().getDeltaTime();
                if(spEnemy->getPhysics()->y < posPlayerY) {spEnemy->getPhysics()->y = posPlayerY;}
                if(estado != Estado_Personaje::atacar) estado = Estado_Personaje::andar;
            }
            else if(posEnemyY < posPlayerY) {
                spEnemy->getPhysics()->y += spEnemy->getPhysics()->vely * ControllerMan::instancia().controller().getDeltaTime();
                if(spEnemy->getPhysics()->y > posPlayerY) {spEnemy->getPhysics()->y = posPlayerY;}
                if(estado != Estado_Personaje::atacar) estado = Estado_Personaje::andar;
            }
        }

        // Si no colisiona el enemigo vuelve a la posición inicial
        if(!colisiona && estado != Estado_Personaje::morir && ((int)posInicial.first != (int)posEnemyX || (int)posInicial.second != (int)posEnemyY)){
            
            if(posEnemyX > posInicial.first) {
                spEnemy->getPhysics()->x -= spEnemy->getPhysics()->velx * ControllerMan::instancia().controller().getDeltaTime();
                if(spEnemy->getPhysics()->x < posInicial.first) {spEnemy->getPhysics()->x = posInicial.first;}
                this->setEstado(Estado_Personaje::andar);
            }
            else if(posEnemyX < posInicial.first) {
                spEnemy->getPhysics()->x += spEnemy->getPhysics()->velx * ControllerMan::instancia().controller().getDeltaTime();
                if(spEnemy->getPhysics()->x > posInicial.first) {spEnemy->getPhysics()->x = posInicial.first;}
                this->setEstado(Estado_Personaje::andar);
            } 
            if(posEnemyY > posInicial.second ) {
                spEnemy->getPhysics()->y -= spEnemy->getPhysics()->vely * ControllerMan::instancia().controller().getDeltaTime();
                if(spEnemy->getPhysics()->y < posInicial.second ) {spEnemy->getPhysics()->y = posInicial.second ;}
                this->setEstado(Estado_Personaje::andar);
            }
            else if(posEnemyY < posInicial.second ) {
                spEnemy->getPhysics()->y += spEnemy->getPhysics()->vely * ControllerMan::instancia().controller().getDeltaTime();
                if(spEnemy->getPhysics()->y > posInicial.second ) {spEnemy->getPhysics()->y = posInicial.second ;}
                this->setEstado(Estado_Personaje::andar);
            }
        }
    }
}

// Disparo del enemigo
Disparo* Enemy::dispararEnemy(Player_t *pl, bool colisiona) {
    Disparo *disp = nullptr; // Creamos un objeto disparo para devolverlo

    if (comportamiento->getTipoIA() == TipoIA::shooter)
    {
        // Comprobamos si el enemigo no puede disparar y si ha recargado para volver a activar el disparo
        if(!puedeDisparar && ControllerMan::instancia().controller().getTimeElapsed() >= timeReload) {puedeDisparar = true;}

        // Si el jugador colisiona con el rango el enemigo disparará hacia la dirección del jugador
        int dir = 0;
        
        if(puedeDisparar && colisiona && estado != Estado_Personaje::morir)
        {
            setEstado(Estado_Personaje::atacar);
            float posX = pl->getSprite()->getPhysics()->x - spEnemy->getPhysics()->x;
            float posY = pl->getSprite()->getPhysics()->y - spEnemy->getPhysics()->y;

            if(posX <= 0 + pl->getSprite()->getWidth() && posX >= 0 - pl->getSprite()->getWidth())
            {
                if(posY >= 0) dir = 4; // Abajo
                else if(posY < 0) dir = 3; // Arriba
            }
            else if(posY <= 0 + pl->getSprite()->getHeight() && posY >= 0 - pl->getSprite()->getHeight())
            {
                if(posX >= 0) dir = 1; // Derecha
                else if(posX < 0) dir = 2; // Izquierdo
            }
            else if(posX > 0 && posY > 0) dir = 7; // Diagonal derecha-abajo
            else if(posX > 0 && posY < 0) dir = 5; // Diagonal derecha-arriba
            else if(posX < 0 && posY > 0) dir = 8; // Diagonal izquierda-abajo
            else if(posX < 0 && posY < 0) dir = 6; // Diagonal izquierda-arriba

            // ***************************** Creamos el disparo *********************************
            std::string textura = "resources/bola_enemy.png";

            //Y creo el spritesheet a partir de la imagen anterior
            Physics_t* phy = new Physics_t();
            Sprite_t* spBola = new Sprite_t(textura, 32 , 32 ,phy);
            spBola->setRoute(textura);
            //Le pongo el centroide donde corresponde

            //Cojo el sprite que me interesa por defecto del sheet

            // Lo dispongo en el centro de la pantalla
            spBola->getPhysics()->x = spEnemy->getPhysics()->x;
            spBola->getPhysics()->y = spEnemy->getPhysics()->y;

            Direction_t direction; // Creamos la dirección
            direction.setDir(dir); // Ponemos la dirección hacia la que irá el disparo
            disp = new Disparo(spBola, damage, tipoMagia, spEnemy->getPhysics()->velx, direction, Objetivo::both);
            ControllerMan::instancia().controller().createShoot(disp->getEntity(), spBola);
            // ***********************************************************************************
            
            puedeDisparar = false; // Desactivamos el disparo del enemigo
            timeReload = ControllerMan::instancia().controller().getTimeElapsed() + cadenciaDisparo; // Guardamos el tiempo + cadencia para ver cuando disparará
        }
    }
    return disp;
}

void Enemy::checkReceive_damage() {
    if(receive_damage)
    {
        if(timeRecover == 0.f)
        {
            timeRecover = ControllerMan::instancia().controller().getTimeElapsed() + inmunity_time;
            nextColor = ControllerMan::instancia().controller().setColorEnemy(entityID, nextColor);
        }
        else
        {
            if(ControllerMan::instancia().controller().getTimeElapsed() >= timeRecover) {
                receive_damage = false;
                timeRecover = 0.f;
                nextColor = ControllerMan::instancia().controller().setColorEnemy(entityID, nextColor);
            }
        }
    }
}

EntityID_t Enemy::getID() {
    return entityID;
}

Hp_t* Enemy::getHp() {
    return hp;
}

void Enemy::setHp(Hp_t* h) {
    hp = h;
}

int Enemy::getDamage() {
    return damage;
}

void Enemy::setDamage(int d) {
    damage = d;
}

float Enemy::getVelocity() {
    return spEnemy->getPhysics()->velx;
}

void Enemy::setVelocity(float vel) {
    spEnemy->getPhysics()->velx = vel;
    spEnemy->getPhysics()->vely = vel;
}

Sprite_t* Enemy::getSprite() {
    return spEnemy;
}

void Enemy::setSprite(Sprite_t *sp) {
    spEnemy = sp;
}

IA* Enemy::getComportamiento() {
    return comportamiento;
}

void Enemy::setComportamiento(IA *ia) {
    comportamiento = ia;
}

int Enemy::getTipoMagia() {
    return tipoMagia;
}

void Enemy::setTipoMagia(int tm) {
    tipoMagia = tm;
}

bool Enemy::getPuedeDisparar() {
    return puedeDisparar;
}

void Enemy::setPuedeDisparar(bool pd) {
    puedeDisparar = pd;
}

float Enemy::getCadenciaDisparo() {
    return cadenciaDisparo;
}

void Enemy::setCadenciaDisparo(float cadencia) {
    cadenciaDisparo = cadencia;
}

std::pair<float,float> Enemy::getPositionInit() {
    return posInicial;
}

void Enemy::setPositionInit(std::pair<float,float> posicionInicial) {
    posInicial = posicionInicial;
}

int Enemy::getPatrolPosition() {
    return patrolPosition;
}

void Enemy::setPatrolPosition(int positionVector) {
    patrolPosition = positionVector;
}

Estado_Personaje Enemy::getEstadoEnemy() {
    return estado;
}

void Enemy::setEnemy(Personajes s) {
    enemy = s;
}

Personajes Enemy::getEnemy() {
    return enemy;
}

bool Enemy::getReceive_damage() {
    return receive_damage;
}

void Enemy::setReceive_damage(bool rd) {
    receive_damage = rd;
}

void Enemy::setEstado(Estado_Personaje s) {
    if(estado != s && estado != Estado_Personaje::morir && estado != Estado_Personaje::atacar){
        estado = s;
        this->getSprite()->frame_r = 0;
    } 
}

void Enemy::setEstado_after_dead(Estado_Personaje s){
    estado = s;
}

float Enemy::getTimeAnimation() {
    return timeAnimation;
}

void Enemy::updateTimeAnimation() {
    timeAnimation = ControllerMan::instancia().controller().getTimeElapsed() + frameTime;
}

void Enemy::setTimeAnimation(float newTime) {
    timeAnimation = newTime;
}

float Enemy::getTimeRespawn() {
    return timeRespawn;
}

void Enemy::updateTimeRespawn() {
    timeRespawn = ControllerMan::instancia().controller().getTimeElapsed() + respawn;
}

void Enemy::setTimeRespawn(float newTime) {
    timeRespawn = newTime;
}
