
#include <iostream>
#include "map.hpp"
#include "include_json.hpp"
using json = nlohmann::json;

std::array<std::string,2> pisable = {"fondo","grass"};


Map_t::~Map_t() {

}

void Map_t::loadMap(int ruta) {
    number_mapa = ruta;
    std::ifstream archivo("resources/Mapas/Mapa_" + std::to_string(ruta) + "/Mapa.JSON");
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

    std::string route = "resources/Mapas/Mapa_"+ std::to_string(ruta) +"/Sprites/";

    for(unsigned int i = 0; i < datasprites.size(); i++ ) {

        std::string name = datasprites[i]["name"].get<std::string>(); 
        route += name + ".png";
        
        bool collisionable = false;
        if(!datasprites[i]["properties"][0]["value"].is_null()){
           collisionable = datasprites[i]["properties"][0]["value"];
        }
        
        bool water = false;
        if(std::strcmp(name.substr(0,4).c_str(),"agua") == 0){
            water = true;
        }

        tipos.emplace_back(
            datasprites[i]["firstgid"].get<int>() ,
            route,
            datasprites[i]["tilewidth"].get<int>() ,
            datasprites[i]["tileheight"].get<int>() ,
            collisionable,
            water
        );
        
        route = "resources/Mapas/Mapa_"+ std::to_string(ruta) +"/Sprites/";
    }

    //std::cout << "Tipos: " << tipos.size() << std::endl;
    //Creamos los respawns donde los personajes tendran que llegar con el kit
    //Objetos
    //auto respawns_one = js["layers"][1]["objects"][0]["x"].get<int>();

    auto respawns_one = js["layers"][3]["objects"][0];

    Physics_t* phy_one = new Physics_t(
        respawns_one["x"].get<int>(),
        respawns_one["y"].get<int>(),
        0.0,
        0.0
    );
    respawn_player_one = new Sprite_t(
        route+respawns_one["name"].get<std::string>()+".png",
        respawns_one["width"],
        respawns_one["height"],
        phy_one
    );

    auto respawns_two = js["layers"][3]["objects"][1];

    Physics_t* phy_two = new Physics_t(
        respawns_two["x"].get<int>(),
        respawns_two["y"].get<int>(),
        0.0,
        0.0
    );
    respawn_player_two = new Sprite_t(
        route+respawns_two["name"].get<std::string>()+".png",
        respawns_two["width"],
        respawns_two["height"],
        phy_two
    );
    //PowerUps
    auto powerUps_json = js["layers"][4]["objects"];
    powerUps.resize(powerUps_json.size());
    for(unsigned int i = 0; i < powerUps_json.size(); i++){
        Physics_t* p = new Physics_t(
            powerUps_json[i]["x"].get<int>(),
            powerUps_json[i]["y"].get<int>(),
            0.0,
            0.0
        );
        Sprite_t* sprite = new Sprite_t(route+"powerup.png",20,30,p);
        Power_Up* pwp = new Power_Up(sprite);
        powerUps[i] = pwp;
    }

    //!Hacer el KIT con el JSON no a mano. De momento lo hago a mano
    auto kit_json = js["layers"][5]["objects"][0];
    Physics_t* phy_kit = new Physics_t(
        kit_json["x"].get<double>(),
        kit_json["y"].get<double>(),
        0.0,
        0.0
    );

    kit_origin = std::pair<double,double>(kit_json["x"].get<double>(),kit_json["y"].get<double>());

    kit = new Sprite_t(
        route+"healing_tile"+".png",
        17,
        15,
        phy_kit
    );
     
    auto spikes_json = js["layers"][6]["objects"];
    for(unsigned int i = 0; i < spikes_json.size(); i++){
        Physics_t* p = new Physics_t(
            spikes_json[i]["x"],
            spikes_json[i]["y"],
            0.0,
            0.0
        );
        spikes_1.push_back(new Sprite_t(route+"spikes.png",20,25,p));
    }

    spikes_json = js["layers"][7]["objects"];
    for(unsigned int i = 0; i < spikes_json.size(); i++){
        Physics_t* p = new Physics_t(
            spikes_json[i]["x"],
            spikes_json[i]["y"],
            0.0,
            0.0
        );
        spikes_2.push_back(new Sprite_t(route+"spikes.png",20,25,p));
    }

    //ES
    auto es_json = js["layers"][8]["objects"];
    auto epu_json = js["layers"][9]["objects"];
    auto epa_json = js["layers"][10]["objects"];

    es.resize(es_json.size()/2); // Es entre 2 por cada enemigo shooter tiene al enemigo y el rango
    epu.resize(epu_json.size()/2); // Es entre 2 por cada enemigo pursuit tiene al enemigo y el rango
    epa.resize(epa_json.size()/2); // Es entre 2 porque minimo tendrá 2 posiciones cada enemigo

    for(unsigned int i = 0; i < epa.size(); i++) {
        epa[i].resize(epa_json.size());
    }

    for(unsigned int i = 0; i < epa_json.size(); i++) {
        auto str = epa_json[i]["name"].get<std::string>();
        int n1 = (int)str[0]-49; // Porque empieza en 1 y no en 0 en el JSON
        int n2 = (int)str[2]-48;
        epa[n1][n2] = std::pair<double,double>(
            epa_json[i]["x"].get<double>(),
            epa_json[i]["y"].get<double>()
        );
    }
    
    for(unsigned int i = 0; i < epa.size(); i++) {
        if(epa[i][0].first == 0.0 && epa[i][0].second == 0.0) {
            epa.resize(i);
            break;
        }
        for (unsigned int j = 0; j < epa[i].size(); j++) {
            if(epa[i][j].first == 0.0 && epa[i][j].second == 0.0) {
                epa[i].resize(j);
                break;
            }
            //std::cout << "Posición " << i << " - " << j << " = " << epa[i][j].first << "; " << epa[i][j].second << std::endl;
        }
    }

    //std::cout << "Size epa = " << epa.size() << std::endl; 

    for(unsigned int i = 0; i < epu_json.size(); i++) {
        auto str = epu_json[i]["name"].get<std::string>();
        int n1 = (int)str[0]-49; // Porque empieza en 1 y no en 0 en el JSON
        int n2 = (int)str[2]-48;
        // Si es 0 es el enemigo si es 1 es el rango
        if(n2 == 0){
            // Si es enemigo (0) cambiamos la posición
            epu[n1] = std::tuple<double, double, double, double>(
                epu_json[i]["x"].get<double>(),
                epu_json[i]["y"].get<double>(),
                std::get<2>(epu[n1]),
                std::get<3>(epu[n1])
            );
        }
        else if(n2 == 1) {
            // Si es rango (1) cambiamos ancho y largo
            epu[n1] = std::tuple<double, double, double, double>(
                std::get<0>(epu[n1]),
                std::get<1>(epu[n1]),
                epu_json[i]["width"].get<double>(),
                epu_json[i]["height"].get<double>()
            );
        }     
    }

    /*for (unsigned i = 0; i < epu.size(); i++)
    {
        std::cout << "Position = " << std::get<0>(epu[i]) << "; " << std::get<1>(epu[i]) << std::endl;
        std::cout << "Width = " << std::get<2>(epu[i]) << "; Height = " << std::get<3>(epu[i]) << std::endl;
    }*/
    

    for(unsigned int i = 0; i < es_json.size(); i++) {
        auto str = es_json[i]["name"].get<std::string>();
        int n1 = (int)str[0]-49; // Porque empieza en 1 y no en 0 en el JSON
        int n2 = (int)str[2]-48;
        // Si es 0 es el enemigo si es 1 es el rango
        if(n2 == 0){
            // Si es enemigo (0) cambiamos la posición
            es[n1] = std::tuple<double, double, double, double>(
                es_json[i]["x"].get<double>(),
                es_json[i]["y"].get<double>(),
                std::get<2>(es[n1]),
                std::get<3>(es[n1])
            );
        }
        else if(n2 == 1) {
            // Si es rango (1) cambiamos ancho y largo
            es[n1] = std::tuple<double, double, double, double>(
                std::get<0>(es[n1]),
                std::get<1>(es[n1]),
                es_json[i]["width"].get<double>(),
                es_json[i]["height"].get<double>()
            );
        }     
    }

    /*for (unsigned i = 0; i < es.size(); i++)
    {
        std::cout << "Position = " << std::get<0>(es[i]) << "; " << std::get<1>(es[i]) << std::endl;
        std::cout << "Width = " << std::get<2>(es[i]) << "; Height = " << std::get<3>(es[i]) << std::endl;
    }*/
    
    //Creamos el Mapa con todos los datos del JSON
    auto hud_json = js["layers"][11]["objects"];

    for(unsigned  int i = 0; i < hud_json.size(); i++){
        hud.insert(
            std::pair<std::string,std::pair<double,double>>(
                hud_json[i]["name"].get<std::string>(),
                std::make_pair<double,double>(
                    hud_json[i]["x"].get<int>(),
                    hud_json[i]["y"].get<int>()
                )
            )
        );
    }

    auto dataMatrix = js["layers"][2]["data"];
    int posX = 10;
    int posY = 10;

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
                    mapaMatrix[i][j]->disparo_water = tipos[t].disparo_water;

                    break;
                }
            }
            posX += 20;
            arr += 1;
        }
        posX = 10;
        posY += 20;
    }

    route = "resources/Mapas/Mapa_"+ std::to_string(ruta)+"/Sprites/Mapa_"+std::to_string(ruta)+".png";
    Physics_t* phy_background = new Physics_t(0.0,0.0,0.0,0);
    background = new Sprite_t(route,widthMap*20,heightMap*20,phy_background);
}