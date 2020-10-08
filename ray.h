#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <optional>
#include "wall.h"

class Ray : public sf::VertexArray{
public:
    Ray(const sf::Vector2f& pos, const sf::Vector2f& dir, float rayLength,
        sf::Color color0 = sf::Color::White, sf::Color color1 = sf::Color::White);

    // Create with only base position and angle to the base (1, 0) vec
    Ray(const sf::Vector2f& pos, double angle);


    // Create without length, just base and direction (default length is 1px)
    Ray(const sf::Vector2f& pos, const sf::Vector2f& dir);


    //change rayLength, and update (*this)[1].position
    void SetRayLength(float rayLength);

    // update the rayLength to match the closest collision
    // return true if at least one collision was found
    bool ProjectOnto(const std::vector<Wall>& wallArray);

    //update the ray based on the current mouse position and the Walls.
    void Update(const sf::Vector2f& mousePosition2f, const std::vector<Wall>& wallArray);

    // Rotate dir
    void RotateBy(double angle);

    void SetRotation(double angle);

public:

static void MakeRays(std::vector<Ray>& rayArray, const sf::Vector2f& mousePosition2f,
                size_t ammount, double angleFacing, double viewingAngle);


static void MakeRays(std::vector<Ray>& rayArray,
                    const sf::Vector2f& mousePosition2f, size_t ammount);


public:
    // the vector's base position, just syntactic sugar
    // and easier access.
    sf::Vector2f& pos = (*this)[0].position;

    // the vector's direction
    sf::Vector2f dir;

    // the vector's angle to the (1, 0)
    double angle;

private:
    // will get rounded down to nearest pixel
    float rayLength;

    // check if they intersect:
    // if they do, return the length of the ray till they do
    // else return an empty optional.
    // it's and std::optional just for fun, it would work better
    // as a simple float with the invalid case as -1.f or something like that. 
    std::optional<float> CheckDist(const Wall& wall);

    // Normalize dir
    void NormalizeDir();


    // Change dir vector and update the tip of the ray accordingly.
    void ChangeDir(float x, float y);

    // recalculate tip   
    void UpdateTip();
};
