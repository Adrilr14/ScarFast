#pragma once

class Ronda{
public:
    Ronda(int numr) : maxrondas(numr) {} ;
    ~Ronda();

    void sumarRonda();
    bool ganarPartida();

private:
    //atributos
    int maxrondas;
    int rondas_player {0};
};
