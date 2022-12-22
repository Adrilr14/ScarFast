#include "enemy.hpp"
#include "../sys/ia.hpp"
#include "player.hpp"
#include "../sys/collision.hpp"

// Constructor
Enemy::Enemy(int n, int h, int d, float vel, sf::Sprite *sp, IA *c) : id(n), hp(h), damage(d), velocity(vel), spEnemy(sp), comportamiento(c) {}

// Destructor
Enemy::~Enemy() {}

// Movimiento del enemigo según el comportamiento
void Enemy::moveEnemy(Player *pl) {

    if (comportamiento->getTipoIA() == TipoIA::patrol)
    {
        // Se mueve de una posición a otra del vector de posiciones 

        // Guardamos las posiciones x e y del enemigo y del vector de patron (se usan enteros para evitar comparaciones muy exactass que no sucedan)
        int posEnemyX = spEnemy->getPosition().x;
        int posEnemyY = spEnemy->getPosition().y;
        int posPatrolX = comportamiento->getPatrol()[patrolPosition].x;
        int posPatrolY = comportamiento->getPatrol()[patrolPosition].y;

        //std::cout << "Posicion enemigo X = " << posEnemyX << "; Posicion enemigo Y = " << posEnemyY << std::endl;
        //std::cout << "Posicion patrulla X = " << posPatrolX << "; Posicion patrulla Y = " << posPatrolY << std::endl;  

        // Si estamos en la posición del la patrulla actual sumamos 1 a patrolPosition (sin que se pase del size)
        if(posEnemyX == posPatrolX && posEnemyY == posPatrolY)
        {
            patrolPosition++;
            if(patrolPosition >= comportamiento->getPatrol().size()) patrolPosition = 0;
        }

        // Comparamos las posiciones para saber hacia donde se tiene que mover el enemigo
        if(posEnemyX < posPatrolX) spEnemy->move(velocity, 0);
        else if(posEnemyX > posPatrolX) spEnemy->move(-velocity, 0);
        if(posEnemyY < posPatrolY) spEnemy->move(0, velocity);
        else if(posEnemyY > posPatrolY) spEnemy->move(0, -velocity);
    }
    
    else if (comportamiento->getTipoIA() == TipoIA::pursuit)
    {
        // Si el jugador colisiona con el rango que tiene va a hacia él para atacarle
    }

    else if(comportamiento->getTipoIA() == TipoIA::nothing)
    {
        // Es estático, no se mueve
    }

    else if (comportamiento->getTipoIA() == TipoIA::shooter)
    {
        // Es estático, no se mueve
    }
}

int Enemy::getHP() {
    return hp;
}

void Enemy::setHP(int h) {
    hp = h;
}

int Enemy::getDamage() {
    return damage;
}

void Enemy::setDamage(int d) {
    damage = d;
}

float Enemy::getVelocity() {
    return velocity;
}

void Enemy::setVelocity(float vel) {
    velocity = vel;
}

sf::Sprite* Enemy::getSprite() {
    return spEnemy;
}

void Enemy::setSprite(sf::Sprite *sp) {
    spEnemy = sp;
}

IA* Enemy::getComportamiento() {
    return comportamiento;
}

void Enemy::setComportamiento(IA *ia) {
    comportamiento = ia;
}
