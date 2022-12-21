#include "physics.hpp"
#include "../facade/ControllerMan.hpp"
#include "../facade/Controller.hpp"

std::tuple<int,int> Physics_t::getPosition() {
    return ControllerMan::instancia().controller().getPositionPlayerone();
}

std::vector<std::pair<int,int>> Physics_t::calcularCuadrante(int x, int y) {
    std::vector<std::pair<int,int>> matrix;
    for(int i = 0; i < cuadrante.size(); i++){
        matrix.emplace_back( (x + cuadrante[i].first ), (y + cuadrante[i].second));
    }
    return matrix;
}