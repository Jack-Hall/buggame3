#include "Enemy.hpp"
#include <cmath>

// Static member initialization
std::random_device Enemy::rd;
std::mt19937 Enemy::gen(Enemy::rd());
std::uniform_real_distribution<float> Enemy::angleDist(0.0f, 2.0f * PI);
std::uniform_real_distribution<float> Enemy::timeDist(1.0f, 3.0f);

Enemy::Enemy(const Vector2& position, EnemyType type) 
    : Entity(position), type(type), speed(50.0f), detectionRadius(100.0f),
      wanderTimer(0.0f), wanderDirection(1, 0) {
    
    originalPosition = position;
    targetPosition = position;
    
    // Set different properties based on enemy type
    switch (type) {
        case EnemyType::WANDERER:
            shape.setFillColor(sf::Color::Green);
            speed = 30.0f;
            radius = 8.0f;
            break;
        case EnemyType::CHASER:
            shape.setFillColor(sf::Color::Red);
            speed = 60.0f;
            radius = 12.0f;
            detectionRadius = 150.0f;
            break;
        case EnemyType::GUARD:
            shape.setFillColor(sf::Color::Blue);
            speed = 40.0f;
            radius = 10.0f;
            detectionRadius = 80.0f;
            break;
    }
    
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
}

void Enemy::update(float deltaTime) {
    if (!active) return;
    
    switch (type) {
        case EnemyType::WANDERER:
            updateWanderer(deltaTime);
            break;
        case EnemyType::CHASER:
            updateChaser(deltaTime);
            break;
        case EnemyType::GUARD:
            updateGuard(deltaTime);
            break;
    }
    
    // Apply velocity
    position += velocity * deltaTime;
    
    // Update visual representation
    shape.setPosition(position.x, position.y);
}

void Enemy::render(sf::RenderWindow& window) {
    if (active) {
        window.draw(shape);
    }
}

void Enemy::updateWanderer(float deltaTime) {
    wanderTimer -= deltaTime;
    
    if (wanderTimer <= 0.0f) {
        // Choose new random direction
        float angle = angleDist(gen);
        wanderDirection = Vector2(std::cos(angle), std::sin(angle));
        wanderTimer = timeDist(gen);
    }
    
    velocity = wanderDirection * speed;
}

void Enemy::updateChaser(float deltaTime) {
    // For now, just wander since there's no player to chase
    // This can be extended later when a player is added
    updateWanderer(deltaTime);
}

void Enemy::updateGuard(float deltaTime) {
    // Guards patrol around their original position
    Vector2 toOriginal = originalPosition - position;
    float distanceFromOriginal = toOriginal.length();
    
    if (distanceFromOriginal > detectionRadius) {
        // Return to original position
        velocity = toOriginal.normalized() * speed;
    } else {
        // Patrol in a small area around original position
        updateWanderer(deltaTime);
        velocity = velocity * 0.5f; // Move slower when patrolling
    }
}
