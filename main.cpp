#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <vector>
#include <cmath>

#define WIDTH 600
#define HEIGHT 600
#define RAY_NUM 100
#define WALL_NUM 20

double Pi = std::acos(-1);
double angleFacing = 0;
double angleOfVision = Pi / 2;

#include "ray.cpp"
#include "wall.cpp"

int main(int argc, char* argv[]){
    srand(time(NULL));

    const size_t RaysAmmount = argc > 1 ? atoi(argv[1]) : RAY_NUM;

    sf::Clock clock;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 3;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "RayCaster", sf::Style::Default, settings);
    window.setFramerateLimit(200);

    std::vector<Wall> wallArray;
    Wall::MakeWalls(wallArray, WALL_NUM);

    std::vector<Ray> rayArray;
    Ray::MakeRays(rayArray, sf::Vector2f(0.f, 0.f), RaysAmmount);

    size_t frameCount = 0;
    float lastAvgFps = 200;
    std::vector<float> last100fps;

    while(window.isOpen()){
        const sf::Vector2f mousePosition2f = 
                        static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

        sf::Event event;

        while(window.pollEvent(event)){
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:

                switch (event.KeyPressed)
                {
                case sf::Keyboard::A :
                    //angleFacing = 
                    //        static_cast<double>(fmodf64(angleFacing + 2*Pi/100, 2*Pi));
                    for(Ray& ray : rayArray)
                        ray.RotateBy(2*Pi/100);
                    break;
                
                case sf::Keyboard::D :
                    //angleFacing = 
                    //        static_cast<double>(fmodf64(angleFacing - 2*Pi/100, 2*Pi));
                    for(Ray& ray : rayArray)
                        ray.RotateBy(-2*Pi/100);
                    break;
                
                default:
                    break;
                }
                wallArray.clear();
                Wall::MakeWalls(wallArray, WALL_NUM);
                break;
            }
        }

        for(const Wall& wall : wallArray){
            window.draw(wall);
        }

        for(Ray& ray : rayArray){
            ray.Update(mousePosition2f, wallArray);
            window.draw(ray);
        }

        window.display();
        window.clear();

        // this is to display average fps every 100 frames:
        if(frameCount == 100){
            // calculate average fps over last100fps

            double sum = 0; // hope we don't overflow :P
            for(float _fps : last100fps){
                sum += _fps;
            }
            float avgFps = sum / 100.f;

            std::cout << "average fps over the last 100 frames : " << avgFps << std::endl;
            
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
