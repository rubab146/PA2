// =============================================================
//  T01 --- Entity: construction, getters, static counter
// =============================================================
#include "../testharness.h"
#include "../../include/Entity.h"

// Concrete stub so we can instantiate Entity
struct ConcreteEntity : public Entity {
    ConcreteEntity(int id, const std::string& name) : Entity(id, name) {}
    void display() const override {}
};

int main() {
    std::cout << "========================================\n";
    std::cout << "  Layer 01 --- Entity\n";
    std::cout << "========================================\n";

    SECTION("Static counter starts at 0");
    CHECK_EQ(Entity::getEntityCount(), 0);

    SECTION("Construction increments entityCount");
    {
        ConcreteEntity e1(1, "Alpha");
        CHECK_EQ(Entity::getEntityCount(), 1);

        ConcreteEntity e2(2, "Beta");
        CHECK_EQ(Entity::getEntityCount(), 2);

        SECTION("Getters return correct values");
        CHECK_EQ(e1.getID(), 1);
        CHECK_EQ(e1.getName(), std::string("Alpha"));
        CHECK_EQ(e2.getID(), 2);
        CHECK_EQ(e2.getName(), std::string("Beta"));
    }
    // e1 and e2 destroyed here

    SECTION("Destruction decrements entityCount back to 0");
    CHECK_EQ(Entity::getEntityCount(), 0);

    SECTION("Multiple construction/destruction cycles");
    {
        ConcreteEntity a(10, "X");
        ConcreteEntity b(11, "Y");
        ConcreteEntity c(12, "Z");
        CHECK_EQ(Entity::getEntityCount(), 3);
    }
    CHECK_EQ(Entity::getEntityCount(), 0);

    SUMMARY();
}
