#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <vector>
#include <cmath>

#define WIDTH 2000
#define HEIGHT 1000
#define WALL_NUM 3

size_t RayAmmount = 100; 
double Pi = std::acos(-1);
double angleFacing = 0;
double angleOfVision = Pi / 2;

#include "ray.cpp"
#include "wall.cpp"


int main(int argc, char* argv[]){
    srand(time(NULL));

    sf::Clock clock;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 3;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "RayCaster", sf::Style::Default, settings);
    window.setFramerateLimit(200);

    std::vector<Wall> wallArray;
    Wall::MakeWalls(wallArray, WALL_NUM);

    std::vector<Ray> rayArray;
    Ray::MakeRays(rayArray, sf::Vector2f(0.f, 0.f), RayAmmount);
    bool shouldAddRay = false; 


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
                std::cout << "key pressed" << std::endl;
                switch (event.key.code)
                {
                case sf::Keyboard::Left :
                    //angleFacing = 
                    //        static_cast<double>(fmodf64(angleFacing + 2*Pi/100, 2*Pi));
                    std::cout << "tried to spin!" << std::endl;
                    for(Ray& ray : rayArray)
                        ray.RotateBy(2*Pi/2000);
                    break;
                
                case sf::Keyboard::Right :
                    //angleFacing = 
                    //        static_cast<double>(fmodf64(angleFacing - 2*Pi/100, 2*Pi));
                    for(Ray& ray : rayArray)
                        ray.RotateBy(-2*Pi/2000);
                    break;

                case sf::Keyboard::N :
                    wallArray.clear();
                    Wall::MakeWalls(wallArray, WALL_NUM);
                    break;

                case sf::Keyboard::M :
                    RayAmmount++;
                    shouldAddRay = true;
                    break;

                }
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

        size_t fpsAmmount = 1000;
        // this is to display average fps every 100 frames:
        if(frameCount == fpsAmmount){
            // calculate average fps over last100fps

            double sum = 0; // hope we don't overflow :P
            for(float _fps : last100fps){
                sum += _fps;
            }
            float avgFps = sum / static_cast<float>(fpsAmmount);

            std::cout << "average fps over the last " << fpsAmmount << " frames : " << avgFps << std::endl;
            
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
