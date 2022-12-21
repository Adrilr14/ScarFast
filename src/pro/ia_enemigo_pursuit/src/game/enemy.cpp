#include "enemy.hpp"
#include "../sys/ia.hpp"
#include "player.hpp"
#include "../sys/collision.hpp"

// Constructor
Enemy::Enemy(int n, int h, int d, float vel, sf::Sprite *sp, IA *c, sf::Vector2f posInicial) : id(n), hp(h), damage(d), velocity(vel), spEnemy(sp), comportamiento(c), posIni(posInicial) {}

// Destructor
Enemy::~Enemy() {}

// Movimiento del enemigo según el comportamiento
void Enemy::moveEnemy(Player *pl) {

    if (comportamiento->getTipoIA() == TipoIA::patrol)
    {
        // Se mueve de una posición a otra del vector de posiciones
    }
    
    else if (comportamiento->getTipoIA() == TipoIA::pursuit)
    {
        // Si el jugador colisiona con el rango que tiene va a hacia él para atacarle
        Collision c;
        bool colisiona = false;
        if(c.collidesWithRange(pl->getSprite(), comportamiento->getRange())){
            float posX = pl->getSprite()->getPosition().x - spEnemy->getPosition().x;
            float posY = pl->getSprite()->getPosition().y - spEnemy->getPosition().y;
            colisiona = true;
            if(posX > 0) spEnemy->move(velocity,0);
            else if(posX < 0) spEnemy->move(-velocity,0);
            
            if(posY > 0) spEnemy->move(0,velocity);
            else if(posY < 0) spEnemy->move(0, -velocity);
            
            //TO DO:: Si colisiona hay que restarle la vida correspondiente
            if(c.collidesWith(pl->getSprite() , spEnemy)) std::cout<<"He colisionado" << std::endl;
        }

        if(!colisiona && posIni != spEnemy->getPosition()){
            
            if(spEnemy->getPosition().x > posIni.x){
              spEnemy->setPosition(spEnemy->getPosition().x-velocity,spEnemy->getPosition().y);  
            } 
            else{
                spEnemy->setPosition(spEnemy->getPosition().x+velocity,spEnemy->getPosition().y);
            } 
            
            if(spEnemy->getPosition().y > posIni.y) spEnemy->setPosition(spEnemy->getPosition().x,spEnemy->getPosition().y-velocity);
            else spEnemy->setPosition(spEnemy->getPosition().x,spEnemy->getPosition().y+velocity);
        }

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