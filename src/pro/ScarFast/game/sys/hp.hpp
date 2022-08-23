#pragma once

class Hp_t {
    
private:
    int hp;
    int shield;
    int max_hp;
    bool invulnerabilidad {false};

public:
    Hp_t(int h = 100,int s = 0);
    ~Hp_t();
    
    bool is_alive();
    void reduceHp(int damage);
    void revivir();

    int getHp();
    void setHp(int vida);
    int getShield();
    void setShield(int escudo);
    void setVulnerabilidad(bool s);
};