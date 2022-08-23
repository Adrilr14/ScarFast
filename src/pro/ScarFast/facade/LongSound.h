#pragma once
#include <iostream>
#include <SFML/Audio.hpp>

using namespace std;

class LongSound {
    public:
        LongSound(string, float);
        

        ~LongSound();


        void play();
        void pause();
        void stop();
        void repetir(bool);
        bool loop();
        bool getEstado(int);
        void volumen(float);

        

    private:       
        sf::Music* musica;  
                      
};