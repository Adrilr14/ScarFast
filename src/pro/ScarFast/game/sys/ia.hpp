#pragma once

#include <iostream>
#include <vector>

// Enumeración para saber que tipo de ia es
enum TipoIA {patrol = 0, shooter = 1, pursuit = 2, nothing = 3};

class IA{

private:
    TipoIA comportamiento;
    std::vector<std::pair<float,float>> patrol;
    std::pair<float,float> range;

public:
    IA(); // Constructor IA para nothing
    IA(std::vector<std::pair<float,float>> patrol); // Constructor IA para patrol
    IA(std::pair<float,float> range, TipoIA comportamiento); // Constructor IA para shooter y pursuit
    ~IA();

    int getTipoIA();

    std::vector<std::pair<float,float>> getPatrol();
    void setPatrol(std::vector<std::pair<float,float>> patrol);

    std::pair<float,float> getRange();
    void setRange(std::pair<float,float> range);
};
