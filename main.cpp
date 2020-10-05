#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <vector>
#include <cmath>

#define WIDTH 600
#define HEIGHT 600
#define RAY_NUM 100
#define WALL_NUM 20
#define PI  3.14159265358979323846

#include "ray.cpp"
#include "wall.cpp"

void MakeRays(std::vector<Ray>& rayArray, const sf::Vector2f& mousePosition2f, size_t size, float length){
    for(float angle = 0; angle <= 2 * PI; angle += (2 * PI) / size){
        rayArray.push_back(Ray(mousePosition2f, sf::Vector2f(std::cos(angle), std::sin(angle)), length));
    }
}

void MakeWalls(std::vector<Wall>& wallArray, size_t size, bool wallsOn = true){
    if(wallsOn){
        wallArray.push_back(Wall(sf::Vector2f(0.f, 0.f), sf::Vector2f((float)WIDTH, 0.f)));
        wallArray.push_back(Wall(sf::Vector2f((float)WIDTH, 0.f), sf::Vector2f((float)WIDTH, (float)HEIGHT)));
        wallArray.push_back(Wall(sf::Vector2f((float)WIDTH, (float)HEIGHT), sf::Vector2f(0.f, (float)WIDTH)));
        wallArray.push_back(Wall(sf::Vector2f(0.f, (float)WIDTH), sf::Vector2f(0.f, 0.f)));
    }
    
    for(int i = 0; i < size; i++){

        float x1 = WIDTH * (float)rand() / RAND_MAX;
        float y1 = HEIGHT * (float)rand() / RAND_MAX;
        float x2 = WIDTH * (float)rand() / RAND_MAX;
        float y2 = HEIGHT * (float)rand() / RAND_MAX;

        wallArray.push_back(Wall(sf::Vector2f(x1, y1), sf::Vector2f(x2, y2)));
    }
}


int main(int argc, char* argv[]){
    srand(time(NULL));

    const size_t RaysAmmount = argc > 1 ? atoi(argv[1]) : RAY_NUM;

    sf::Clock clock;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 100;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML", sf::Style::Default, settings);

    std::vector<Wall> wallArray;
    MakeWalls(wallArray, WALL_NUM);

    std::vector<Ray> rayArray;
    MakeRays(rayArray, sf::Vector2f(0.f, 0.f), RaysAmmount, 500.f);

    size_t frameCount = 0; 
    std::vector<float> last100fps; 

    while(window.isOpen()){
        const sf::Vector2f mousePosition2f = (sf::Vector2f)sf::Mouse::getPosition(window);
        sf::Event event;
        while(window.pollEvent(event)){
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                wallArray.clear();
                MakeWalls(wallArray, WALL_NUM);
                break;
            }
        }

        for(const Wall& wall : wallArray){
            window.draw(wall);
        }

        for(Ray& ray : rayArray){
            ray[0].position = mousePosition2f;
            if(ray.ProjectOnto(wallArray))
                window.draw(ray);
        }

        window.display();
        window.clear();

        // this is to display average fps every 100 frames:
        if(frameCount == 100){
            // calculate average fps over last100fps

            float sum = 0; // hope we don't overflow 
            for(float _fps : last100fps){
                sum += _fps;
            }

            std::cout << "average fps over the last 100 frames : " << sum / 100.f << std::endl;
            
            frameCount = 0; 
            last100fps.clear();
            clock.restart();
            
        } else {
            last100fps.push_back(1.f / clock.restart().asSeconds());
            frameCount++;
        }
    }
    return 0;
}