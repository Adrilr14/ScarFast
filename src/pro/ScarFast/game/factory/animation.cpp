#include "animation.hpp"
#include "include_json.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
using json = nlohmann::json;

void Animation_t::load_animations(std::string nombre) {
    std::ifstream archivo(nombre);
    std::stringstream buffer;
    buffer << archivo.rdbuf();
    std::string jsonString = buffer.str();
    json js = json::parse(jsonString);
    archivo.close();
    estados.resize(numMax+1);
    estados[numMax] = new States();
    
    for(unsigned int j = 0; j < js["frames"].size(); j++){
        std::string delimiter = "_";
        std::string accion = js["frames"][j]["filename"].get<std::string>().substr(0, js["frames"][j]["filename"].get<std::string>().find(delimiter));
        //std::cout<<"accion: "<<accion<<std::endl;
        frames_t* s = new frames_t();
        
        s->x = js["frames"][j]["frame"]["x"].get<int>();
        s->y = js["frames"][j]["frame"]["y"].get<int>();
        s->w = js["frames"][j]["frame"]["w"].get<int>();
        s->h = js["frames"][j]["frame"]["h"].get<int>();
        

        if("Attacking" == accion || "Attack" == accion) estados[numMax]->attacking.push_back(s);
        else if("Walking" == accion) estados[numMax]->walking_r.push_back(s);
        else if("Dying" == accion) estados[numMax]->dying.push_back(s);
        else if("Idle" == accion) estados[numMax]->parado.push_back(s);
        //std::cout<<"accion: "<<accion<<std::endl;
    }
    numMax++;
}