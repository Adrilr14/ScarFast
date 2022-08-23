#ifndef MainSound_H
#define MainSound_H


#include<iostream>
#include<string>
#include<map>

//Librerias facade

#include "../facade/Buffer.h"
#include "../facade/ShortSound.h"
#include "../facade/LongSound.h"


class MainSound
{
private:
	
	std::map<std::string, ShortSound*> sonidos;
	std::map<std::string, LongSound*> musica;

	bool pause;
public:
	MainSound();
	virtual ~MainSound();
	//sonidos
	void activarShortSound(std::string estado,Buffer*,float);
	void play(const std::string estado);	
	void stop(const std::string estado);	

	void setPause();
	//musica
	void activarLongSound(std::string estado,string ruta,float);
	void playLongSound(const std::string estado);	
	void stop2(const std::string estado);	

};

#endif