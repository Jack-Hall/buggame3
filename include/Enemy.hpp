#pragma once
#include "constants.hpp"
#include "Entity.hpp"
#include <random>

enum class EnemyType {
    WANDERER,
    CHASER,
    GUARD
};

class Enemy : public Entity {
public:
    Enemy(const Vector2& position, EnemyType type = EnemyType::WANDERER);
    
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    
    void setTarget(const Vector2& target) { targetPosition = target; }
    EnemyType getType() const { return type; }
    
private:
    void updateWanderer(float deltaTime);
    void updateChaser(float deltaTime);
    void updateGuard(float deltaTime);
    
    EnemyType type;
    Vector2 targetPosition;
    Vector2 originalPosition;  // For guard type
    float speed;
    float detectionRadius;
    
    // AI state
    float wanderTimer;
    Vector2 wanderDirection;
    
    // Random number generation
    static std::random_device rd;
    static std::mt19937 gen;
    static std::uniform_real_distribution<float> angleDist;
    static std::uniform_real_distribution<float> timeDist;
};
