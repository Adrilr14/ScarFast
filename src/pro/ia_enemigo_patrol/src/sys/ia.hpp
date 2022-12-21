#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

// Enumeración para saber que tipo de ia es
enum TipoIA {patrol = 0, shooter = 1, pursuit = 2, nothing = 3};

class IA{

private:
    TipoIA comportamiento;
    std::vector<sf::Vector2f> patrol;
    sf::RectangleShape *range;

public:
    IA(); // Constructor IA para nothing
    IA(std::vector<sf::Vector2f> patrol); // Constructor IA para patrol
    IA(sf::RectangleShape *range, TipoIA comportamiento); // Constructor IA para shooter y pursuit
    ~IA();

    int getTipoIA();

    std::vector<sf::Vector2f> getPatrol();
    void setPatrol(std::vector<sf::Vector2f> patrol);

    sf::RectangleShape* getRange();
    void setRange(sf::RectangleShape *range);
};
