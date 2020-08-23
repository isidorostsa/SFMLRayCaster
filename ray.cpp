#include "ray.h"

Ray::Ray(sf::Vector2f pos, sf::Vector2f dir, float rayLength, sf::Color color0, sf::Color color1) : dir(dir), rayLength(rayLength), sf::VertexArray(sf::Lines, 2){
    (*this)[0].position = pos;
    (*this)[1].position = pos + rayLength * dir;
    
    (*this)[0].color = color0;
    (*this)[1].color = color1;
    
    Normalize();
}


void Ray::SetRayLength(float rayLength){
    this->rayLength = rayLength;
    (*this)[1].position = pos + (rayLength * dir);
}



void Ray::Normalize(){
    float magnitude = dir.x*dir.x + dir.y*dir.y;
    if(magnitude != 1){
       dir.x /= sqrt((double)magnitude);
       dir.y /= sqrt((double)magnitude);
    }
}


float Ray::CheckDist(const Wall& wall){

// first determine if they intersect
// if they do we must have u>=0, 0<=t<=1
// where ray.pos + u * ray.dir = wall.a + t * (wall.b - wall.a)
    float u, t;

// cross product defined as VxW = Vx*Wy - Vy*Wx
    const float rdxwd = dir.x*wall.dir.y - dir.y*wall.dir.x;

// if wall is non existant, they don't intersect
    if(wall.dir.x == 0 and wall.dir.y == 0)
        return -1.f;
    
// if ray is parallel to the wall, they don't intersect
    if(rdxwd == 0)
        return -1.f;

//  now we can divide fearlessly:
    u = ((wall.pos.x - pos.x)*wall.dir.y - (wall.pos.y - pos.y)*wall.dir.x) / rdxwd;
    t = -((pos.x - wall.pos.x)*dir.y - (pos.y - wall.pos.y)*dir.x) / rdxwd;

    if(u < 0 or t < 0 or t > 1)
        return -1.f;

// since our conditions are met we know they intersect at the point so:
// point = ray.pos + u * ray.dir = wall.pos + t * wall.dir
    return u;
}


bool Ray::Intersect(const std::vector<Wall>& wallArray){
    
    float minDist = INFINITY;
    bool intersected = false;

    for(const Wall& wall : wallArray){
        float distance = CheckDist(wall);
        if(0 < distance and distance < minDist){
            intersected = true;
            minDist = distance;
        }
    }
    
    if(intersected){
        SetRayLength(minDist);
        // std::cout << "length set to:" << minDist << std::endl;
        return true;
    }

    return false;
}
