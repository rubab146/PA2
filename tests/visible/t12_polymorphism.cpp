// =============================================================
//  T12 --- Runtime polymorphism: virtual dispatch through base pointers
// =============================================================
#include "../testharness.h"
#include "../../include/Entity.h"
#include "../../include/Cargo.h"
#include "../../include/Vessel.h"
#include "../../include/LightFreighter.h"
#include "../../include/HeavyLifter.h"
#include "../../include/StealthRunner.h"
#include "../../include/StandardCargo.h"
#include "../../include/HazardousCargo.h"
#include "../../include/PerishableCargo.h"

int main() {
    std::cout << "========================================\n";
    std::cout << "  Layer 12 --- Runtime Polymorphism\n";
    std::cout << "========================================\n";

    // ---- getEffectiveWeight via Cargo* ----
    SECTION("getEffectiveWeight dispatched correctly through Cargo*");
    {
        Cargo* items[3];
        items[0] = new StandardCargo (1, "S", 10.0);   // eff = 10.0
        items[1] = new HazardousCargo(2, "H",  5.0);   // eff =  6.0
        items[2] = new PerishableCargo(3,"P",  2.0, 3); // eff =  7.0

        CHECK_NEAR(items[0]->getEffectiveWeight(), 10.0, 0.001);
        CHECK_NEAR(items[1]->getEffectiveWeight(),  6.0, 0.001);
        CHECK_NEAR(items[2]->getEffectiveWeight(),  7.0, 0.001);

        for (int i = 0; i < 3; i++) delete items[i];
    }

    // ---- calculateFuel via Vessel* ----
    SECTION("calculateFuel dispatched correctly through Vessel*");
    {
        Vessel* vessels[3];
        vessels[0] = new LightFreighter(1, "LF");
        vessels[1] = new HeavyLifter   (2, "HL");
        vessels[2] = new StealthRunner (3, "SR", 0.5);

        // Load 10 kg standard cargo on each
        for (int i = 0; i < 3; i++)
            vessels[i]->addCargo(new StandardCargo(100+i, "C", 10.0));

        // LF: 100 * 10 * 0.5 = 500
        CHECK_NEAR(vessels[0]->calculateFuel(100),  500.0,  0.1);
        // HL: 100 * 10 * 1.5 + 500 = 2000
        CHECK_NEAR(vessels[1]->calculateFuel(100), 2000.0,  0.1);
        // SR: 100 * 10 * 0.5 = 500
        CHECK_NEAR(vessels[2]->calculateFuel(100),  500.0,  0.1);

        for (int i = 0; i < 3; i++) delete vessels[i];
    }

    // ---- display() via Vessel* ----
    SECTION("display() dispatched correctly through Vessel*");
    {
        Vessel* lf = new LightFreighter(4, "Alpha");
        Vessel* hl = new HeavyLifter   (5, "Beta");
        Vessel* sr = new StealthRunner (6, "Gamma", 0.75);

        lf->addCargo(new StandardCargo(201, "X", 5.0));
        hl->addCargo(new StandardCargo(202, "Y", 5.0));
        sr->addCargo(new StandardCargo(203, "Z", 5.0));

        CAPTURE_COUT(sLF);
        lf->display();
        std::string outLF = STOP_CAPTURE(sLF);

        CAPTURE_COUT(sHL);
        hl->display();
        std::string outHL = STOP_CAPTURE(sHL);

        CAPTURE_COUT(sSR);
        sr->display();
        std::string outSR = STOP_CAPTURE(sSR);

        CHECK_CONTAINS(outLF, "LightFreighter");
        CHECK_CONTAINS(outHL, "HeavyLifter");
        CHECK_CONTAINS(outSR, "StealthRunner");
        CHECK_CONTAINS(outSR, "CloakRating");

        delete lf; delete hl; delete sr;
    }

    // ---- Polymorphic clone via Vessel* ----
    SECTION("clone() via Vessel* returns correct derived type and data");
    {
        Vessel* orig = new StealthRunner(7, "CloneTest", 0.4);
        orig->addCargo(new StandardCargo(301, "Gem", 8.0));

        Vessel* copy = orig->clone();
        CHECK_NOT_NULL(copy);

        // Same fuel calculation (same type + same data)
        CHECK_NEAR(copy->calculateFuel(50),
                   orig->calculateFuel(50), 0.001);

        // Independent
        orig->addCargo(new StandardCargo(302, "Extra", 2.0));
        CHECK(orig->getCurrentLoad() > copy->getCurrentLoad());

        delete orig;
        delete copy;
    }

    // ---- Polymorphic clone via Cargo* ----
    SECTION("clone() via Cargo* returns correct effective weight");
    {
        Cargo* original = new HazardousCargo(401, "Rad", 10.0, 4);
        Cargo* cloned   = original->clone();

        CHECK_NOT_NULL(cloned);
        CHECK_NEAR(cloned->getEffectiveWeight(), 12.0, 0.001);  // 10 * 1.2
        CHECK(cloned != original);

        delete original;
        delete cloned;
    }

    SECTION("All counters return to 0");
    CHECK_EQ(Entity::getEntityCount(),         0);
    CHECK_EQ(Cargo::getTotalCargoCreated(),     0);
    CHECK_EQ(Vessel::getTotalVesselsCreated(),  0);

    SUMMARY();
}
