#include "enemy.hpp"
#include "../sys/ia.hpp"
#include "player.hpp"
#include "../sys/collision.hpp"
#include "disparo.hpp"

// Constructores
Enemy::Enemy(int n, int h, int d, float vel, sf::Sprite *sp, IA *c) : id(n), hp(h), damage(d), velocity(vel), spEnemy(sp), comportamiento(c), tipoMagia (0), puedeDisparar(false), cadenciaDisparo(0.f) {}

Enemy::Enemy(int n, int h, int d, float vel, sf::Sprite *sp, IA *c, int tm, float cadencia) : id(n), hp(h), damage(d), velocity(vel), spEnemy(sp), comportamiento(c), tipoMagia (tm), puedeDisparar(true), cadenciaDisparo(cadencia) {}

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

// Disparo del enemigo
Disparo* Enemy::dispararEnemy(Player *pl) {
    Disparo *disp = nullptr; // Creamos un objeto disparo para devolverlo
    if (comportamiento->getTipoIA() == TipoIA::shooter)
    {
        // Si el jugador colisiona con el rango el enemigo disparará hacia la dirección del jugador
        Collision c;
        int dir = 0;
        
        if(c.collidesWithRange(pl->getSprite(), comportamiento->getRange()))
        {
            float posX = pl->getSprite()->getPosition().x - spEnemy->getPosition().x;
            float posY = pl->getSprite()->getPosition().y - spEnemy->getPosition().y;

            if(posX <= 0 + pl->getSprite()->getTextureRect().width && posX >= 0 - pl->getSprite()->getTextureRect().width)
            {
                if(posY >= 0) dir = 3; // Arriba
                else if(posY < 0) dir = 4; // Abajo
            }
            else if(posY <= 0 + pl->getSprite()->getTextureRect().height && posY >= 0 - pl->getSprite()->getTextureRect().height)
            {
                if(posX >= 0) dir = 1; // Derecha
                else if(posX < 0) dir = 2; // Izquierdo
            }
            else if(posX > 0 && posY > 0) dir = 5; // Diagonal derecha-arriba
            else if(posX > 0 && posY < 0) dir = 7; // Diagonal derecha-abajo
            else if(posX < 0 && posY > 0) dir = 6; // Diagonal izquierda-arriba
            else if(posX < 0 && posY < 0) dir = 8; // Diagonal izquierda-abajo

            // ***************************** Creamos el disparo *********************************
            sf::Texture *tex = new sf::Texture;
            if (!(tex->loadFromFile("resources/bola.png"))) 
            {
                std::cerr << "Error cargando la imagen sprites.png";
                exit(0);
            }

            //Y creo el spritesheet a partir de la imagen anterior
            sf::Sprite *spBola = new sf::Sprite(*tex);

            //Le pongo el centroide donde corresponde
            spBola->setOrigin(64/2, 64/2);
            //Cojo el sprite que me interesa por defecto del sheet
            spBola->setTextureRect(sf::IntRect(0*64,0*64, 64, 64));

            // Lo dispongo en ela posición del enemigo
            spBola->setPosition(spEnemy->getPosition().x, spEnemy->getPosition().y);
            disp = new Disparo(1, spBola, damage, tipoMagia, velocity, nullptr, dir);
            // ***********************************************************************************
            
        }
    }
    return disp;
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
