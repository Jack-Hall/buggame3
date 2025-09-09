#pragma once
#include "Entity.hpp"
#include <vector>

class CollisionManager {
public:
    std::vector<Entity*> objects;
    CollisionManager();
    ~CollisionManager();
    void registerObject(Entity* object);
    void checkCollisions();
};
