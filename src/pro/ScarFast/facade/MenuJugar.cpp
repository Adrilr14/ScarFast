#include "MenuJugar.hpp"

MenuJugar::MenuJugar(int width, int height, int item){
sounds = new MainSound();
    sounds->activarLongSound("intro", ("resources/sounds/Intro.wav"), 30);
    sounds->activarShortSound("click", (new Buffer("resources/sounds/click.wav")), 60);

    if(!textBack.loadFromFile("resources/fondoJugar.jpg")){
        exit(0);
    }
    if(!textGol.loadFromFile("resources/golemMenu.png")){
        exit(0);
    }
    if(!textMino.loadFromFile("resources/minoMenu.png")){
        exit(0);
    }

    if(!textDer.loadFromFile("resources/derecha.png")){
        exit(0);
    }
    if(!textIzq.loadFromFile("resources/izquierda.png")){
        exit(0);
    }

    for(int i=0; i<2; i++){
        botonDer[i].setTexture(textDer);
        botonDer[i].setScale(sf::Vector2f(0.3, 0.3));
    }
    for(int i=0; i<2; i++){
        botonIzq[i].setTexture(textIzq);
        botonIzq[i].setScale(sf::Vector2f(0.3, 0.3));
    }


    botonIzq[0].setPosition(sf::Vector2f(360, 240));
    botonDer[0].setPosition(sf::Vector2f(740, 240));

    botonIzq[1].setPosition(sf::Vector2f(1200, 240));
    botonDer[1].setPosition(sf::Vector2f(1540, 240));

    background.setTexture(textBack);
    background.setTextureRect(sf::IntRect(0,0, (int)width, (int)height));

    golem.setTexture(textGol);
    golem.setScale(sf::Vector2f(0.5, 0.5));
    golem.setPosition(sf::Vector2f(400, 150));

    mino.setTexture(textMino);
    mino.setScale(sf::Vector2f(0.5, 0.5));
    mino.setPosition(sf::Vector2f(1200, 150));

    font.loadFromFile("resources/fonts/fuente.ttf");

    texto[0][0].setFont(font);
    texto[0][0].setString("Jugador 1");
    texto[0][0].setCharacterSize(50);
    texto[0][0].setColor(sf::Color::Blue);
    texto[0][0].setPosition(sf::Vector2f((width / 2 - (50/8)*2) - 500, (height / (Max_items + 1)* 1)-150)); 

    texto[0][1].setFont(font);
    texto[0][1].setString("Jugador 2");
    texto[0][1].setCharacterSize(50);
    texto[0][1].setColor(sf::Color::Blue);
    texto[0][1].setPosition(sf::Vector2f((width / 2 - (50/8)*2) + 300, (height / (Max_items + 1)* 1)-150)); 

    texto[1][0].setFont(font);
    texto[1][0].setString("Facil");
    texto[1][0].setCharacterSize(50);
    texto[1][0].setColor(sf::Color::White);
    texto[1][0].setPosition(sf::Vector2f((width / 2 - (50/5)*2) - 500, (height / (Max_items + 1)* 3))); 
    
    texto[1][1].setFont(font);
    texto[1][1].setString("Dificil");
    texto[1][1].setCharacterSize(50);
    texto[1][1].setColor(sf::Color::White);
    texto[1][1].setPosition(sf::Vector2f((width / 2 - (50/7)*2) + 300, (height / (Max_items + 1)* 3))); 

    texto[2][0].setFont(font);
    texto[2][0].setString("Jugar");
    texto[2][0].setCharacterSize(50);
    texto[2][0].setColor(sf::Color::White);
    texto[2][0].setPosition(sf::Vector2f(width / 2 - (50*5)/2, height / (Max_items + 1)* 4)); 

    texto[3][0].setFont(font);
    texto[3][0].setString("Atras");
    texto[3][0].setCharacterSize(50);
    texto[3][0].setColor(sf::Color::White);
    texto[3][0].setPosition(sf::Vector2f(width / 2- (50*5)/2, height / (Max_items + 1)* 5)); 

    itemSelected = 0;
}

MainSound* MenuJugar::getSound(){
    return sounds;
}

void MenuJugar::draw(sf::RenderWindow &window){
    window.draw(background);
    for (size_t i = 0; i < Max_items; i++)
    {
        for( int j = 0; j<2; j++){
            window.draw(texto[i][j]);
        }
    }
    window.draw(golem);
    window.draw(mino);

    for(int i=0; i<2; i++){
        window.draw(botonIzq[i]);
        window.draw(botonDer[i]);
    }
}

void MenuJugar::MoveUp(){
    if(itemSelected - 1 >= 0){
        if(itemSelected == 0){
            texto[itemSelected][0].setColor(sf::Color::Blue);

        }else{
            if(itemSelected == 0){
                texto[0][0].setColor(sf::Color::Yellow);
                texto[0][1].setColor(sf::Color::Yellow);
                //std::cout<<"MENU\n";
            }
            if( itemSelected == 1 ){
                texto[0][1].setColor(sf::Color::Blue);
                if(estado){
                    texto[1][0].setColor(sf::Color::Yellow);
                    texto[1][1].setColor(sf::Color::White);
                }else{
                    texto[1][0].setColor(sf::Color::White);
                    texto[1][1].setColor(sf::Color::Yellow);
                }
            }else{
                texto[itemSelected][0].setColor(sf::Color::White);
            }
        }
        itemSelected--;
        if( itemSelected == 0){
            texto[0][0].setColor(sf::Color::Yellow);
            texto[0][1].setColor(sf::Color::Yellow);
        }
        if(itemSelected!=1){
            texto[itemSelected][0].setColor(sf::Color::Yellow);
        }
    }
}

void MenuJugar::MoveDown(){
    if(itemSelected - 1 < Max_items){
        if(itemSelected == 0){
            texto[itemSelected][0].setColor(sf::Color::Blue);

        }else{
            if(itemSelected == 0){
                texto[0][0].setColor(sf::Color::Yellow);
                texto[0][1].setColor(sf::Color::Yellow);
                //std::cout<<"MENU\n";
            }else{
                texto[0][0].setColor(sf::Color::Blue);
                texto[0][1].setColor(sf::Color::Blue);
            }
            if(itemSelected == 1 ){
                texto[0][1].setColor(sf::Color::Blue);
                if(estado){
                    texto[1][0].setColor(sf::Color::Yellow);
                    texto[1][1].setColor(sf::Color::White);

                }else{
                    texto[1][0].setColor(sf::Color::White);
                    texto[1][1].setColor(sf::Color::Yellow);
                }
            }else{
                texto[0][1].setColor(sf::Color::Blue);
                texto[itemSelected][0].setColor(sf::Color::White);
            }
        }
        itemSelected++;
        if(itemSelected!=1){
            texto[itemSelected][0].setColor(sf::Color::Yellow);
        }
    }
}

void MenuJugar::move(int color){
    if(color != 0){
        if(color%2 == 0){        
            estado = true;
            texto[1][0].setColor(sf::Color::Yellow);
            texto[1][1].setColor(sf::Color::White);

        }else{
            estado = false;
            texto[1][0].setColor(sf::Color::White);
            texto[1][1].setColor(sf::Color::Yellow);
        }
    }
}

int MenuJugar::GetItemSelected(){
    return itemSelected;
}

void MenuJugar::cambiarSprite(int aux, int comp){
    if(aux == 0){
        if(comp%2 == 0 && comp!=0){
            textGol.loadFromFile("resources/golemMenu.png");
            golem.setTexture(textGol);
            golem.setScale(sf::Vector2f(0.5, 0.5));
            golem.setPosition(sf::Vector2f(400, 150));
            jugador1 = 1;
        }else{
            textGol.loadFromFile("resources/minoMenu.png");
            golem.setTexture(textGol);
            golem.setScale(sf::Vector2f(0.5, 0.5));
            golem.setPosition(sf::Vector2f(400, 150));
            jugador1 = 0;
        }
    }else{
        if(comp%2 == 0 && comp!=0){
            textMino.loadFromFile("resources/minoMenu.png");
            mino.setTexture(textMino);
            mino.setScale(sf::Vector2f(0.5, 0.5));
            mino.setPosition(sf::Vector2f(1200, 150));
            jugador2 = 0;
        }else{
            textMino.loadFromFile("resources/golemMenu.png");
            mino.setTexture(textMino);
            mino.setScale(sf::Vector2f(0.5, 0.5));
            mino.setPosition(sf::Vector2f(1200, 150));
            jugador2 = 1;
        }
    }
}

void MenuJugar::elegirMapa(int m){
    std::srand(std::time(nullptr));
    if(m%2 == 0){
        mapa = 3+rand()%4;
    }else{
        mapa = 5+rand()%6;
    }
}

int MenuJugar::getMapa(){
    return mapa;
}

void MenuJugar::setMapa(int map){
    mapa = map;
}

int MenuJugar::getJugador1(){
    return jugador1;
}

void MenuJugar::setJugador1(int j1){
    jugador1 = j1;
}

int MenuJugar::getJugador2(){
    return jugador2;
}

void MenuJugar::setJugador2(int j2){
    jugador2 = j2;
}