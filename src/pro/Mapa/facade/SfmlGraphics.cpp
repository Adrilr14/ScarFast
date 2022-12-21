#include "SfmlGraphics.hpp"
#include <iostream>

#include "../game/sys/direction.hpp"


void SfmlGraphics::createWindow(int width, int height) {
    window = new sf::RenderWindow(sf::VideoMode(width,height),"Test");
}

bool SfmlGraphics::isWindowOpen() {
    if(window->isOpen()){
        return true;
    }
    return false;
}

void SfmlGraphics::setEnviroment() {
    tex = new sf::Texture();
    if (!tex->loadFromFile("resources/Mapas/Mapa1/Sprites/0000.png")) {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }

    if (!tex2.loadFromFile("resources/Mapas/Mapa1/Sprites/fondo.png")) {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }

    //Y creo el spritesheet a partir de la imagen anterior
    sprite = new sf::Sprite(*tex);
    sprite2 = sf::Sprite(tex2);

    //Le pongo el centroide donde corresponde
    sprite->setOrigin(10, 10);
    //Cojo el sprite que me interesa por defecto del sheet
    //sprite->setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));

    // Lo dispongo en el centro de la pantalla
    sprite->setPosition(10,260);
    sprite2.setPosition(320, 240);

    //Prueba para cargar el mapa
        
    //map.load_Map();
}

void SfmlGraphics::checkControlls(Keyboard_t* k, Direction_t* dir) {
    //Bucle de obtención de eventos
    bool busca = false;
    sf::Event event;
    while (window->pollEvent(event)) {
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            k->button_W = true;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            k->button_A = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            k->button_S = true;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            k->button_D = true;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            dir->dirPrevia = dir->dir;
            dir->dir = 1;

            k->button_Right = true;

            oldPosSp = sprite->getPosition();
            for(unsigned int i = 0; i < dir->dirCollision.size();i++){
                if(dir->dirCollision[i] == dir->dir){
                    busca = true;
                    break;
                }
            }
            if(!busca){
                sprite->move(5, 0);
            }
            //sprite->setTextureRect(sf::IntRect(9, 157, 51, 65));
            //Escala por defecto
            sprite->setScale(1, 1);

            //Si colisiona se restaura la posicion
            /*for(int i = 0; i < solidos.size();i++){
                if (checkCollisions(sprite, solidos[i])){
                    std::cout << "CHOCA : " << std::endl;
                    sprite->setPosition(oldPosSp);
                }
            }*/
        
        
        //sprite->setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
        //Escala por defecto

        sprite->setScale(1, 1);
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            dir->dirPrevia = dir->dir;
            dir->dir = 2;
            k->button_Left = true;
            //sprite->setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
            //Reflejo vertical
            sprite->setScale(-1, 1);
            for(unsigned int i = 0; i < dir->dirCollision.size();i++){
                if(dir->dirCollision[i] == dir->dir){
                    busca = true;
                    break;
                }
            }
            if(!busca){
                sprite->move(-5, 0);
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            dir->dirPrevia = dir->dir;
            dir->dir = 3;
            k->button_Up = true;
            //sprite->setTextureRect(sf::IntRect(0 * 75, 3 * 75, 75, 75));
            for(unsigned int i = 0; i < dir->dirCollision.size();i++){
                if(dir->dirCollision[i] == dir->dir){
                    busca = true;
                    break;
                }
            }
            if(!busca){
                sprite->move(0, -5);
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            dir->dirPrevia = dir->dir;
            dir->dir = 4;
            k->button_Down = true;
            //sprite->setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));
            for(unsigned int i = 0; i < dir->dirCollision.size();i++){
                if(dir->dirCollision[i] == dir->dir){
                    busca = true;
                    break;
                }
            }
            if(!busca){
                sprite->move(0, 5);
            }
        }

        switch (event.type) {

        //Si se recibe el evento de cerrar la ventana la cierro
        case sf::Event::Closed:
            window->close();
            break;

        //Se pulsó una tecla, imprimo su codigo
        case sf::Event::KeyPressed:

            //Verifico si se pulsa alguna tecla de movimiento
            switch (event.key.code) {

                //Tecla ESC para salir
                case sf::Keyboard::Escape:
                window->close();
                break;

                //Cualquier tecla desconocida se imprime por pantalla su código
                default:
                std::cout << event.key.code << std::endl;
                break;
            }
        }
    }
}

void SfmlGraphics::run() {

    window->clear();
    //window->draw(sprite2);
    //window->draw(map);

    for(unsigned int i = 0; i < this->sprites.size(); i++) {
        for(unsigned int j = 0; j < this->sprites[i].size(); j++){
            if(this->sprites[i][j] != NULL){
                window->draw(*sprites[i][j]);
            }
        }
    }
    window->draw(*sprite);
    window->display();
}

void SfmlGraphics::load_MapSfml(Map_t& mapa) {
    //Mejorar esto: NO ES EFICIENTE HAY UNA FORMA MEJOR
    sprites.resize(mapa.getHeightMap(), std::vector<sf::Sprite*>(mapa.getWithMap()));
    this->map = mapa;
    for(unsigned int i = 0; i < mapa.getMatrizMapa().size(); i++){
        for(unsigned int j = 0; j < mapa.getMatrizMapa()[i].size(); j++){
            if(mapa.getMatrizMapa()[i][j] != nullptr){
                sf::Texture* tex = new sf::Texture();
                tex->loadFromFile(mapa.getMatrizMapa()[i][j]->getRoute());
                sf::Sprite* spr = new sf::Sprite(*tex);
                spr->setPosition(
                    mapa.getMatrizMapa()[i][j]->getPhysics()->x,
                    mapa.getMatrizMapa()[i][j]->getPhysics()->y
                );
                spr->setOrigin(
                    mapa.getMatrizMapa()[i][j]->getWidth(),
                    mapa.getMatrizMapa()[i][j]->getHeight()
                );
                texturesMap.push_back(tex);
                sprites[i][j] = spr;
            }
        }
    }
}

bool SfmlGraphics::checkCollisions(sf::Sprite *sp1, sf::Sprite *sp2) {
     bool colisiona = false;
    if (sp1->getGlobalBounds().intersects(sp2->getGlobalBounds()))
    {
        colisiona = true;
    }
     return colisiona;
}

std::tuple<int,int> SfmlGraphics::getPositionPlayerone() {
    return std::tuple<int,int>(sprite->getPosition().x,sprite->getPosition().y);
}

std::tuple<int,int> SfmlGraphics::getPositionSprite(int x, int y) {
    return std::tuple<int,int>(sprites[x][y]->getPosition().x, sprites[x][y]->getPosition().y);
}

bool SfmlGraphics::load_Sprites(Entity_ID id, std::string v) {
    //Loading Sprites like characters, power-ups etc.
}
