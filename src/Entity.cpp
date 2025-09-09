#include "Entity.hpp"

Entity::Entity(const Vector2& position) 
    : position(position), velocity(0, 0), radius(10.0f), active(true) {
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setFillColor(sf::Color::White);
}

bool Entity::collidesWith(const Entity& other) const {
    if (!active || !other.active) return false;
    
    float distance = position.distance(other.position);
    return distance < (radius + other.radius);
}

void Entity::onCollision(const Entity& other) {
    // Do nothing by default
}