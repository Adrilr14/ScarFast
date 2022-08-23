#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include "Buffer.h"

using namespace std;

class ShortSound {
    public:
        ShortSound(Buffer*,float);
        

        ~ShortSound();


        void setBuffer(Buffer*);
        void play();
        void pause();
        void stop();
        void repetir(bool);
        bool loop();
        bool getEstado(int);
        void volumen(float);
       // void setTime(Tiempo time);     

    private:  
        sf::Sound* sonido; 
      
                      
};