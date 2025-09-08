#include "Game.hpp"
#include <iostream>

Game::Game() 
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bug Game 3 - SFML"),
      world(std::make_unique<World>(WORLD_WIDTH, WORLD_HEIGHT)),
      cameraPosition(WORLD_WIDTH / 2.0f, WORLD_HEIGHT / 2.0f) {
    
    window.setFramerateLimit(60);
    
    // Set up camera
    camera.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    camera.setCenter(cameraPosition.x, cameraPosition.y);
    window.setView(camera);
}

Game::~Game() = default;

void Game::run() {
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
                
            case sf::Event::KeyPressed:
                // Camera movement with arrow keys
                if (event.key.code == sf::Keyboard::Left) {
                    cameraPosition.x -= 50.0f;
                } else if (event.key.code == sf::Keyboard::Right) {
                    cameraPosition.x += 50.0f;
                } else if (event.key.code == sf::Keyboard::Up) {
                    cameraPosition.y -= 50.0f;
                } else if (event.key.code == sf::Keyboard::Down) {
                    cameraPosition.y += 50.0f;
                } else if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                break;
                
            default:
                break;
        }
    }
}

void Game::update(float deltaTime) {
    world->update(deltaTime);
    
    // Keep camera within world bounds
    float halfWidth = WINDOW_WIDTH / 2.0f;
    float halfHeight = WINDOW_HEIGHT / 2.0f;
    
    if (cameraPosition.x - halfWidth < 0) cameraPosition.x = halfWidth;
    if (cameraPosition.x + halfWidth > WORLD_WIDTH) cameraPosition.x = WORLD_WIDTH - halfWidth;
    if (cameraPosition.y - halfHeight < 0) cameraPosition.y = halfHeight;
    if (cameraPosition.y + halfHeight > WORLD_HEIGHT) cameraPosition.y = WORLD_HEIGHT - halfHeight;
    
    camera.setCenter(cameraPosition.x, cameraPosition.y);
    window.setView(camera);
}

void Game::render() {
    window.clear(sf::Color(20, 20, 30)); // Dark background
    
    world->render(window);
    
    window.display();
}
