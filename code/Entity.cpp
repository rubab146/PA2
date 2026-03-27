#include "../include/Entity.h"

// static member definition
int Entity::entityCount = 0;

Entity::Entity(int id, const std::string &name)
{
    // TODO
    this->name = name;
    this->id = id;
    entityCount++;
}

Entity::Entity(const Entity &other)
{
    // TODO
    this->id = other.id;
    this->name = other.name;
    entityCount++;
}

Entity::~Entity()
{
    // TODO
    entityCount--;
}

int Entity::getID() const
{
    // TODO
    return id; // placeholder
}

std::string Entity::getName() const
{
    // TODO
    return name; // placeholder
}

int Entity::getEntityCount()
{
    // TODO
    return entityCount; // placeholder
}
