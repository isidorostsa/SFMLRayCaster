#include "wall.h"

Wall::Wall(sf::Vector2f point1, sf::Vector2f point2) : sf::VertexArray(sf::Lines, 2){
    (*this)[0].position = point1;
    (*this)[1].position = point2;
    dir = (*this)[1].position - (*this)[0].position;
}
