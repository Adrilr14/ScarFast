#pragma once

#define SET_UP_FOR_GAME 4

class Temporizador_t {

private:
    //Datos que nosotros queremos en el temporizador
    float aumentoTiempo {0.f};
    int minuto; 
    int segundo;

    int aux = -1;
public:

    Temporizador_t(int tiempo_as_seconds) {
        minuto  = tiempo_as_seconds/60;
        segundo = tiempo_as_seconds%60; 
        aux = tiempo_as_seconds;
    }

    void getTime();
    void startCounting();
    bool still_time_to_process();
};