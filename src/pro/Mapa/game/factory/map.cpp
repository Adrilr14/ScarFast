#include "map.hpp"

#include <iostream>

#include "include_json.hpp"
using json = nlohmann::json;

std::array<std::string,2> pisable = {"fondo","grass"};


Map_t::~Map_t() {

}

void Map_t::Load_Map() {
    std::ifstream archivo("resources/Mapas/Mapa1/mapa1.JSON");
    std::stringstream buffer;
    buffer << archivo.rdbuf();
    std::string jsonString = buffer.str();
    json js = json::parse(jsonString);
    archivo.close();

    //Cargamos los elementos que necesitamos del Mapa
    widthMap  = js["layers"][0]["width"].get<int>();
    heightMap = js["layers"][0]["height"].get<int>();

    mapaMatrix.resize(heightMap, std::vector<Sprite_t*>(widthMap));

    std::vector<Sprite_t> tipos;

    auto datasprites = js["tilesets"];

    std::string route = "resources/Mapas/Mapa1/Sprites/";

    for(unsigned int i = 0; i < datasprites.size(); i++ ) {

        std::string name = datasprites[i]["name"].get<std::string>(); 
        route += name + ".png";
        
        bool collisionable = true;
        if( (std::strcmp(pisable[0].c_str(), name.c_str() ) == 0) || (std::strcmp(pisable[1].c_str(), name.c_str() ) == 0) ){
            collisionable = false;
        }
        
        tipos.emplace_back(
            datasprites[i]["firstgid"].get<int>() ,
            route,
            datasprites[i]["tilewidth"].get<int>() ,
            datasprites[i]["tileheight"].get<int>() ,
            collisionable
        );
        
        route = "resources/Mapas/Mapa1/Sprites/";
    }

    //Creamos el Mapa con todos los datos del JSON
    auto dataMatrix = js["layers"][0]["data"];
    int posX = 20;
    int posY = 20;

    int arr = 0;
    for(unsigned int i = 0; i < mapaMatrix.size(); i++) {
        for(unsigned int j = 0; j < mapaMatrix[i].size(); j++) {
            for(unsigned int t = 0; t < tipos.size(); t++) {
                if(!dataMatrix[arr].is_null() && dataMatrix[arr].get<int>() == tipos[t].getID()){
                    Physics_t* p = new Physics_t();
                    p->x = posX;
                    p->y = posY;
                    mapaMatrix[i][j] = new Sprite_t(
                        tipos[t].getID(),
                        tipos[t].getRoute(),
                        tipos[t].getWidth(),
                        tipos[t].getHeight(),
                        tipos[t].getCollisionable(),
                        p
                    );
                    //std::cout << "i j " << i << " " << j << std::endl;
                    //std::cout << dataMatrix[arr] << " " << arr << std::endl;
                    arr += 1;
                    posX += 20;
                    break;
                }
            }
        }
        posX = 20;
        posY += 20;
    }
}