// =============================================================
//  T11 --- Static counters: live counts correct; all reach 0
// =============================================================
#include "../testharness.h"
#include "../../include/Entity.h"
#include "../../include/Cargo.h"
#include "../../include/Vessel.h"
#include "../../include/Hub.h"

int main() {
    std::cout << "========================================\n";
    std::cout << "  Layer 11 --- Static Counters\n";
    std::cout << "========================================\n";

    SECTION("All counters start at 0 before any construction");
    CHECK_EQ(Entity::getEntityCount(),         0);
    CHECK_EQ(Cargo::getTotalCargoCreated(),     0);
    CHECK_EQ(Vessel::getTotalVesselsCreated(),  0);

    SECTION("entityCount tracks live Entity-derived objects");
    {
        Hub h;
        h.loadFleet("fleet.txt");
        // fleet.txt has 3 vessels (3 entities) + 8 cargo items (8 entities) = 11
        int entityTotal = Entity::getEntityCount();
        CHECK(entityTotal > 0);

        int cargoTotal  = Cargo::getTotalCargoCreated();
        CHECK(cargoTotal > 0);

        int vesselTotal = Vessel::getTotalVesselsCreated();
        CHECK(vesselTotal > 0);

        SECTION("Cargo counter matches actual cargo count");
        // 3 (Firefly) + 3 (Goliath) + 2 (Phantom) = 8
        CHECK_EQ(cargoTotal, 8);

        SECTION("Vessel counter matches actual vessel count");
        // 3 vessels in fleet.txt
        CHECK_EQ(vesselTotal, 3);

        SECTION("Counter increases after copy");
        Hub copy(h);
        CHECK_EQ(Vessel::getTotalVesselsCreated(), vesselTotal * 2);
        CHECK_EQ(Cargo::getTotalCargoCreated(),   cargoTotal  * 2);
        // copy goes out of scope here
    }
    // h and copy are both gone

    SECTION("All counters return to 0 after all objects destroyed");
    CHECK_EQ(Entity::getEntityCount(),         0);
    CHECK_EQ(Cargo::getTotalCargoCreated(),     0);
    CHECK_EQ(Vessel::getTotalVesselsCreated(),  0);

    SECTION("Counters survive multiple hub create/destroy cycles");
    for (int i = 0; i < 3; i++) {
        Hub h;
        h.loadFleet("fleet.txt");
    }
    CHECK_EQ(Entity::getEntityCount(),         0);
    CHECK_EQ(Cargo::getTotalCargoCreated(),     0);
    CHECK_EQ(Vessel::getTotalVesselsCreated(),  0);

    SUMMARY();
}
