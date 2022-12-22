#pragma once
#include <fstream>
#include <sstream>
#include <vector>

enum types {
    tipo_solido,
    tipo_powerup
};

class Collision_t {

private:
    std::vector<std::vector<int>> solidos;
    std::vector<std::vector<int>> power_up;
public:
    Collision_t(){};
    ~Collision_t();
    void load_Bounding_Box(std::vector<int> elementos,types e);
};