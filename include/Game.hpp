#pragma once
#include "World.hpp"
#include "CollisionManager.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class Game {
public:
    Game();
    ~Game();
    
    void run();
    
private:
    void processEvents();
    void update(float deltaTime);
    void render();
    
    sf::RenderWindow window;
    std::unique_ptr<World> world;
    sf::Clock clock;
    
    // Game settings
    static const int WINDOW_WIDTH = 1200;
    static const int WINDOW_HEIGHT = 800;
    static const int WORLD_WIDTH = 1600;
    static const int WORLD_HEIGHT = 1200;
    
    // Camera/View
    sf::View camera;
    Vector2 cameraPosition;
};
