#include "hud.h"
#include <iostream> 

Hud::Hud(){
    vida = 100;
    if(vida>100){
        vida=100;
    }
    if(!textura.loadFromFile("resources/corazon_pixel.png")){
        exit(0);
    }
    if(!textArma.loadFromFile("resources/bola.png")){
        exit(0);
    }
    corLleno.setTexture(textura);
    corMedio.setTexture(textura);
    corLleno.setTextureRect(sf::IntRect (0, 0, 33, 32));
    corMedio.setTextureRect(sf::IntRect (33, 0, 66, 32));

    arma.setTexture(textArma);
    arma.setTextureRect(sf::IntRect(0, 0, 64, 64));
}

void Hud::dibujarCorazon(sf::RenderWindow &vent){
    int aux = vida/2;
    int suma = 0;
    if(vida > 0){
        if(aux>10){
            for(int i=0; i<aux/10; i++){
                corLleno.setPosition(50+suma, 50);
                vent.draw(corLleno);
                suma+=30;
            }
        }else{
            if(aux==10){
                corLleno.setPosition(50, 50);
                vent.draw(corLleno);
            }
            if(aux==5){
                corMedio.setPosition(50, 50);
                vent.draw(corMedio);
            }
        }
        if(aux%10 == 5){
            corMedio.setPosition(50+30*(aux/10), 50);
            vent.draw(corMedio);
        }
    }
}

void Hud::pintarObjeto(int x, sf::RenderWindow &vent){
    if(x==1){
        arma.setPosition(55, 80);
        arma.setScale(0.4, 0.4);
        vent.draw(arma);
        std::cout<<"Entra\n";
    }
}

void Hud::bajarVida(int x){
    vida-=x;
    if(vida<0){
        vida=0;
    }
}