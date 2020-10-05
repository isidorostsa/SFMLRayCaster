#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <optional>
#include "wall.h"

class Ray : public sf::VertexArray{
private:
    float rayLength;

    // check if they intersect:
    // if they do, return the length of the ray till they do
    // else return 0.
    std::optional<float> CheckDist(const Wall& wall);

public:
    Ray(sf::Vector2f pos, sf::Vector2f dir, float rayLength, sf::Color color0 = sf::Color::White, sf::Color color1 = sf::Color::White);

    sf::Vector2f& pos = (*this)[0].position;
    sf::Vector2f dir;

    //change rayLength, and update (*this)[1].position
    void SetRayLength(float rayLength);
    
    // Normalize dir
    void Normalize();


    // update the rayLength to match the closest collision
    // return true if at least one collision was found
    bool ProjectOnto(const std::vector<Wall>& wallArray);

};
