// =============================================================
//  T04 --- Vessel Rule of Three: deep copy, self-assignment
// =============================================================
#include "../testharness.h"
#include "../../include/LightFreighter.h"
#include "../../include/StandardCargo.h"
#include "../../include/HazardousCargo.h"

// Helper: build a vessel with two cargo items
static LightFreighter* makeLoaded(int id, const std::string& name) {
    LightFreighter* v = new LightFreighter(id, name);
    v->addCargo(new StandardCargo(1, "ItemA", 10.0));
    v->addCargo(new HazardousCargo(2, "ItemB", 5.0, 3));
    return v;
}

int main() {
    std::cout << "========================================\n";
    std::cout << "  Layer 04 --- Vessel Rule of Three\n";
    std::cout << "========================================\n";

    // ---- Copy Constructor ----
    SECTION("Copy constructor produces independent deep copy");
    {
        LightFreighter* orig = makeLoaded(1, "Origin");
        LightFreighter copy(*orig);

        CHECK_EQ(copy.getCurrentLoad(),  orig->getCurrentLoad());
        CHECK_EQ(copy.getMaxCapacity(),  orig->getMaxCapacity());
        CHECK_NEAR(copy.getTotalWeight(),
                   orig->getTotalWeight(), 0.001);

        SECTION("Copy constructor: modifying original does not affect copy");
        orig->addCargo(new StandardCargo(3, "Extra", 7.0));
        // orig now has 3 items; copy should still have 2
        CHECK_EQ(orig->getCurrentLoad(), 3);
        CHECK_EQ(copy.getCurrentLoad(),  2);

        SECTION("Copy constructor: both track totalVesselsCreated separately");
        int beforeDel = Vessel::getTotalVesselsCreated();
        CHECK(beforeDel >= 2);

        delete orig;
        int afterDel = Vessel::getTotalVesselsCreated();
        CHECK_EQ(afterDel, beforeDel - 1);
        // copy is still alive; deleting orig must not corrupt copy
        CHECK_NEAR(copy.getTotalWeight(), 16.0, 0.001); // 10.0 + 5.0*1.2
    }

    // ---- Copy Assignment Operator ----
    SECTION("Copy assignment operator produces independent deep copy");
    {
        LightFreighter* src = makeLoaded(2, "Source");
        LightFreighter dst(3, "Dest");

        dst = *src;

        CHECK_EQ(dst.getCurrentLoad(),  src->getCurrentLoad());
        CHECK_NEAR(dst.getTotalWeight(),
                   src->getTotalWeight(), 0.001);

        SECTION("Copy assignment: modifying src does not affect dst");
        src->addCargo(new StandardCargo(4, "NewItem", 3.0));
        CHECK_EQ(src->getCurrentLoad(), 3);
        CHECK_EQ(dst.getCurrentLoad(),  2);

        SECTION("Copy assignment: deleting src does not corrupt dst");
        double savedWeight = dst.getTotalWeight();
        delete src;
        CHECK_NEAR(dst.getTotalWeight(), savedWeight, 0.001);
    }

    // ---- Self-assignment ----
    SECTION("Self-assignment guard: vessel = vessel does not crash");
    {
        LightFreighter v(5, "SelfTest");
        v.addCargo(new StandardCargo(5, "Cargo", 5.0));
        double wBefore = v.getTotalWeight();

        v = v;   // self-assignment — must not crash or corrupt

        CHECK_NEAR(v.getTotalWeight(), wBefore, 0.001);
        CHECK_EQ(v.getCurrentLoad(), 1);
    }

    SECTION("All vessel counters return to 0");
    CHECK_EQ(Vessel::getTotalVesselsCreated(), 0);

    SUMMARY();
}
