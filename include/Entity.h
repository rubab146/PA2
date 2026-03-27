#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity {
private:
    static int entityCount;

protected:
    int id;
    std::string name;

public:
    Entity(int id, const std::string& name);
    Entity(const Entity& other);
    virtual ~Entity();

    int         getID()   const;
    std::string getName() const;
    static int  getEntityCount();

    virtual void display() const = 0;
};

#endif // ENTITY_H
