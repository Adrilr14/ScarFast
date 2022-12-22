#pragma once

enum Max_rondas {
    ronda_min   = 1,
    ronda_inter = 3,
    ronda_max   = 5
};

class Ronda_t {
    public:
        Ronda_t(Max_rondas r) : maxr(r){};
        void sumarRonda(int i);
        int tryGanarPartida();
        void resetPuntuaje();
        int getPunuaje(int pos);

    private:
        Max_rondas maxr;
        int ronda=0;
        int puntuaje[2] = {0,0};
};