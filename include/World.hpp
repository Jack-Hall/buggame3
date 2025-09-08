#pragma once
#include "Enemy.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class World {
public:
    World(int width, int height);
    
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    
    void spawnEnemy(const Vector2& position, EnemyType type = EnemyType::WANDERER);
    void spawnRandomEnemies(int count);
    
    bool isPositionValid(const Vector2& position, float radius = 0.0f) const;
    Vector2 getRandomValidPosition() const;
    
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
private:
    void createBoundaries();
    void handleCollisions();
    
    int width, height;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<sf::RectangleShape> boundaries;
    
    // Random generation
    mutable std::random_device rd;
    mutable std::mt19937 gen;
};
