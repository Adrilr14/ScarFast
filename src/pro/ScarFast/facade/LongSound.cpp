#include "LongSound.h"


using namespace std;

//Constructor
LongSound::LongSound(string ruta, float volume) {
    musica = new sf::Music();
    if (!musica->openFromFile(ruta)) {
        exit(0);
    }
    musica->setVolume(volume);
    
}

//Destructor
LongSound::~LongSound() {
    delete musica;
}


void LongSound::play() {
    musica->play();
}

void LongSound::pause() {
    musica->pause();
}

void LongSound::stop() {
    musica->stop();
}

bool LongSound::loop() {
    return musica->getLoop();
}
void LongSound::repetir(bool loop) {
    musica->setLoop(loop);
}


void LongSound::volumen(float volume) {
    musica->setVolume(volume);
}


bool LongSound::getEstado(int status){

    
    switch(status){
        case 0: 
            if(musica->getStatus()==sf::Music::Status::Playing){
                return true;
            }
        break;
        case 1:
            if(musica->getStatus()==sf::Music::Status::Stopped){
                return true;
            } 
        break;
        case 2:
            if(musica->getStatus()==sf::Music::Status::Paused){
                return true;
            }  
        break;
    
        default: return false;

    }
    return false;

}

