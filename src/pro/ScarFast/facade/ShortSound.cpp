#include "ShortSound.h"


using namespace std;

//Constructor
ShortSound::ShortSound(Buffer* buffer,float volume) {
    sonido = new sf::Sound();
    sonido->setBuffer(*buffer->getBuffer());
    sonido->setVolume(volume);
    
}

//Destructor
ShortSound::~ShortSound() {
    delete sonido;
}

void ShortSound::setBuffer(Buffer* buffer) {
    sonido->setBuffer(*buffer->getBuffer());
    
}

void ShortSound::play() {
    sonido->play();
}

void ShortSound::pause() {
    sonido->pause();
}

void ShortSound::stop() {
    sonido->stop();
}

bool ShortSound::loop() {
    return sonido->getLoop();
}

void ShortSound::volumen(float volume) {
    sonido->setVolume(volume);
}


bool ShortSound::getEstado(int status){

    
    switch(status){
        case 0: 
            if(sonido->getStatus()==sf::Sound::Status::Playing){
                return true;
            }
        break;
        case 1:
            if(sonido->getStatus()==sf::Sound::Status::Stopped){
                return true;
            } 
        break;
        case 2:
            if(sonido->getStatus()==sf::Sound::Status::Paused){
                return true;
            }  
        break;
    
        default: return false;

    }
    return false;

}
