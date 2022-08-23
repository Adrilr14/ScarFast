#include "MainSound.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../facade/Buffer.h"
#include "../facade/ShortSound.h"


MainSound::MainSound(){
	pause=false;
}

MainSound::~MainSound()
{
	for(auto i=sonidos.begin(); i != sonidos.end(); ++i) {
        delete sonidos.find(i->first)->second;
    }
	sonidos.clear();
}

void MainSound::activarShortSound(std::string estado, Buffer* buffer, float volume)
{
	this->sonidos[estado] = new ShortSound(buffer, volume);
	
}

void MainSound::play(const std::string estado)
{	
	
		if((sonidos[estado]->getEstado(1)) ){
			this->sonidos[estado]->play();
		}		
}

void MainSound::stop(const std::string estado)
{	
	
		this->sonidos[estado]->stop();		
}

void MainSound::stop2(const std::string estado)
{	
	
		//this->musica[estado]->stop();		
}


void MainSound::setPause()
{
	if(this->pause){
		pause=false;
	}else{
		pause=true;
	}
}


//Musica


void MainSound::activarLongSound(std::string estado, string ruta, float volume)
{
	this->musica[estado] = new LongSound(ruta, volume);
	
}

void MainSound::playLongSound(const std::string estado)
{	
	
		
		this->musica[estado]->play();
		this->musica[estado]->repetir(true);

				
}


