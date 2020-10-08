#include "wall.h"

Wall::Wall(sf::Vector2f point1, sf::Vector2f point2) : sf::VertexArray(sf::Lines, 2){
    (*this)[0].position = point1;
    (*this)[1].position = point2;
    dir = (*this)[1].position - (*this)[0].position;
}


void Wall::MakeWalls(std::vector<Wall>& wallArray, size_t size){
    //draw the border walls
    wallArray.emplace_back(sf::Vector2f(0.f, 0.f), sf::Vector2f(WIDTH, 0.f));
    wallArray.emplace_back(sf::Vector2f(WIDTH, 0.f), sf::Vector2f(WIDTH, HEIGHT));
    wallArray.emplace_back(sf::Vector2f(WIDTH, HEIGHT), sf::Vector2f(0.f, HEIGHT));
    wallArray.emplace_back(sf::Vector2f(0.f, HEIGHT), sf::Vector2f(0.f, 0.f));

    for(size_t i = 0; i < size; i++){

        float x1 = WIDTH * (float)rand() / RAND_MAX;
        float y1 = HEIGHT * (float)rand() / RAND_MAX;
        float x2 = WIDTH * (float)rand() / RAND_MAX;
        float y2 = HEIGHT * (float)rand() / RAND_MAX;

        wallArray.push_back(Wall(sf::Vector2f(x1, y1), sf::Vector2f(x2, y2)));
    }
}
