#include "CollisionManager.hpp"


CollisionManager::CollisionManager() { 
    objects = std::vector<Entity*>();
}

CollisionManager::~CollisionManager() { 

}

void CollisionManager::registerObject(Entity* object) { 
    objects.push_back(object);
}

void CollisionManager::checkCollisions() { 

    for (int i = 0; i < objects.size(); i++) {
        for ( int j = i + 1; j < objects.size(); j++) {
            if ( objects[i]->collidesWith(*objects[j])) {
                objects[i]->onCollision(*objects[j]);
                objects[j]->onCollision(*objects[i]);
            }
        }
    }
}