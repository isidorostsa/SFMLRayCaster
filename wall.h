#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

// TODO: simple 4 floats constructor.

class Wall : public sf::VertexArray{
public:
    // read only access to the 2 points
    Wall(sf::Vector2f point1, sf::Vector2f point2);

    sf::Vector2f& pos = (*this)[0].position;
    sf::Vector2f dir;
public:
    static void MakeWalls(std::vector<Wall>& wallArray, size_t ammount);
};