#pragma once
#include "Vector2.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class Entity {
public:
    Entity(const Vector2& position = Vector2(0, 0));
    virtual ~Entity() = default;
    
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    
    const Vector2& getPosition() const { return position; }
    void setPosition(const Vector2& pos) { position = pos; }
    
    float getRadius() const { return radius; }
    void setRadius(float r) { radius = r; }
    
    bool isActive() const { return active; }
    void setActive(bool a) { active = a; }
    
    // Collision detection
    bool collidesWith(const Entity& other) const;
    
protected:
    Vector2 position;
    Vector2 velocity;
    float radius;
    bool active;
    sf::CircleShape shape;
};
