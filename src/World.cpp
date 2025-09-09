#include "World.hpp"
#include <random>

World::World(int width, int height) :collisionManager(), width(width), height(height), gen(rd()) {
    createBoundaries();
    spawnRandomEnemies(15); // Start with 15 enemies

}

void World::update(float deltaTime) {
    // Update all enemies
    for (auto& enemy : enemies) {
        enemy->update(deltaTime);
        
        // Keep enemies within world bounds
        Vector2 pos = enemy->getPosition();
        float radius = enemy->getRadius();
        
        if (pos.x - radius < 0 || pos.x + radius > width ||
            pos.y - radius < 0 || pos.y + radius > height) {
            
            // Bounce off walls by reversing velocity and moving back in bounds
            Vector2 newPos = pos;
            if (pos.x - radius < 0) newPos.x = radius;
            if (pos.x + radius > width) newPos.x = width - radius;
            if (pos.y - radius < 0) newPos.y = radius;
            if (pos.y + radius > height) newPos.y = height - radius;
            
            enemy->setPosition(newPos);
        }
    }
    
}

void World::render(sf::RenderWindow& window) {
    // Render boundaries
    for (const auto& boundary : boundaries) {
        window.draw(boundary);
    }
    
    // Render enemies
    for (const auto& enemy : enemies) {
        enemy->render(window);
    }
}

void World::spawnEnemy(const Vector2& position, EnemyType type) {
    if (isPositionValid(position, 15.0f)) {
        enemies.push_back(std::make_unique<Enemy>(position, type));
        collisionManager.registerObject(enemies.back().get());
    }
}

void World::spawnRandomEnemies(int count) {
    std::uniform_int_distribution<int> typeDist(0, 2);
    
    for (int i = 0; i < count; ++i) {
        Vector2 pos = getRandomValidPosition();
        EnemyType type = static_cast<EnemyType>(typeDist(gen));
        spawnEnemy(pos, type);
    }
}

bool World::isPositionValid(const Vector2& position, float radius) const {
    // Check world boundaries
    if (position.x - radius < 0 || position.x + radius > width ||
        position.y - radius < 0 || position.y + radius > height) {
        return false;
    }
    
    // Check collision with existing enemies
    for (const auto& enemy : enemies) {
        if (position.distance(enemy->getPosition()) < radius + enemy->getRadius() + 5.0f) {
            return false;
        }
    }
    
    return true;
}

Vector2 World::getRandomValidPosition() const {
    std::uniform_real_distribution<float> xDist(50.0f, width - 50.0f);
    std::uniform_real_distribution<float> yDist(50.0f, height - 50.0f);
    
    Vector2 position;
    int attempts = 0;
    const int maxAttempts = 100;
    
    do {
        position = Vector2(xDist(gen), yDist(gen));
        attempts++;
    } while (!isPositionValid(position, 15.0f) && attempts < maxAttempts);
    
    return position;
}

void World::createBoundaries() {
    const float borderThickness = 5.0f;
    
    // Top border
    sf::RectangleShape topBorder(sf::Vector2f(width, borderThickness));
    topBorder.setPosition(0, 0);
    topBorder.setFillColor(sf::Color(100, 100, 100));
    boundaries.push_back(topBorder);
    
    // Bottom border
    sf::RectangleShape bottomBorder(sf::Vector2f(width, borderThickness));
    bottomBorder.setPosition(0, height - borderThickness);
    bottomBorder.setFillColor(sf::Color(100, 100, 100));
    boundaries.push_back(bottomBorder);
    
    // Left border
    sf::RectangleShape leftBorder(sf::Vector2f(borderThickness, height));
    leftBorder.setPosition(0, 0);
    leftBorder.setFillColor(sf::Color(100, 100, 100));
    boundaries.push_back(leftBorder);
    
    // Right border
    sf::RectangleShape rightBorder(sf::Vector2f(borderThickness, height));
    rightBorder.setPosition(width - borderThickness, 0);
    rightBorder.setFillColor(sf::Color(100, 100, 100));
    boundaries.push_back(rightBorder);
}


