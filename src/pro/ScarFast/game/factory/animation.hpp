#pragma once

#include <vector>
#include <string>

struct frames_t{
    int x,y;
    int w,h;
    frames_t() = default;
};

struct States {
    std::string name = "";
    std::vector<frames_t*> walking_r{};
    std::vector<frames_t*> attacking{};
    std::vector<frames_t*> dying{};
    std::vector<frames_t*> parado{};
};

class Animation_t {

public:
    //4 estados
    std::vector<States*> estados;
    int numMax      {0};
    int cantidad    {0};

    Animation_t() = default;
    ~Animation_t();

    void load_animations(std::string nombre);
};