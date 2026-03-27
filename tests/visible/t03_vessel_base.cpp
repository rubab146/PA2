// =============================================================
//  T03 --- Vessel base: construction, addCargo overloads,
//          getTotalWeight, static counter
// =============================================================
#include "../testharness.h"
#include "../../include/LightFreighter.h"
#include "../../include/StandardCargo.h"
#include "../../include/HazardousCargo.h"
#include "../../include/PerishableCargo.h"

int main() {
    std::cout << "========================================\n";
    std::cout << "  Layer 03 --- Vessel Base\n";
    std::cout << "========================================\n";

    SECTION("totalVesselsCreated starts at 0");
    CHECK_EQ(Vessel::getTotalVesselsCreated(), 0);

    // ---- Constructor overloads ----
    SECTION("Constructor overload 1: default capacity = 10");
    {
        LightFreighter lf(1, "Firefly");
        CHECK_EQ(lf.getMaxCapacity(),   10);
        CHECK_EQ(lf.getCurrentLoad(),    0);
        CHECK_EQ(lf.getID(),             1);
        CHECK_EQ(lf.getName(), std::string("Firefly"));
        CHECK_EQ(Vessel::getTotalVesselsCreated(), 1);
    }
    CHECK_EQ(Vessel::getTotalVesselsCreated(), 0);

    SECTION("Constructor overload 2: custom capacity");
    {
        LightFreighter lf(2, "Nimble", 5);
        CHECK_EQ(lf.getMaxCapacity(), 5);
        CHECK_EQ(lf.getCurrentLoad(), 0);
    }

    // ---- addCargo overload 1 (append) ----
    SECTION("addCargo overload 1: appends in order, increments currentLoad");
    {
        LightFreighter lf(3, "TestShip");
        Cargo* c1 = new StandardCargo(101, "ItemA", 10.0);
        Cargo* c2 = new HazardousCargo(102, "ItemB", 5.0, 2);
        Cargo* c3 = new PerishableCargo(103, "ItemC", 2.0, 7);

        lf.addCargo(c1);
        CHECK_EQ(lf.getCurrentLoad(), 1);
        lf.addCargo(c2);
        CHECK_EQ(lf.getCurrentLoad(), 2);
        lf.addCargo(c3);
        CHECK_EQ(lf.getCurrentLoad(), 3);

        SECTION("getTotalWeight: sums effective weights via polymorphism");
        // Standard: 10.0, Hazardous: 5.0*1.2=6.0, Perishable: 2.0+5=7.0
        CHECK_NEAR(lf.getTotalWeight(), 23.0, 0.001);
    }

    SECTION("addCargo overload 1: prints message when capacity full");
    {
        LightFreighter lf(4, "TinyShip", 2);
        lf.addCargo(new StandardCargo(201, "A", 1.0));
        lf.addCargo(new StandardCargo(202, "B", 1.0));
        CHECK_EQ(lf.getCurrentLoad(), 2);

        CAPTURE_COUT(ss);
        lf.addCargo(new StandardCargo(203, "C", 1.0));
        std::string out = STOP_CAPTURE(ss);

        // Vessel is responsible for the pointer when capacity is full
        // (student must delete it) - we only check the message here
        CHECK_CONTAINS(out, "Capacity Reached");
    }

    // ---- addCargo overload 2 (slot placement) ----
    SECTION("addCargo overload 2: places cargo at specified slot");
    {
        LightFreighter lf(5, "SlotShip", 5);
        Cargo* c = new StandardCargo(301, "Gadget", 4.0);

        bool ok = lf.addCargo(c, 2);
        CHECK(ok == true);

        SECTION("addCargo overload 2: returns false for occupied slot");
        Cargo* c2 = new StandardCargo(302, "Widget", 2.0);
        bool dup = lf.addCargo(c2, 2);
        CHECK(dup == false);
        delete c2;  // not stored; student must free it

        SECTION("addCargo overload 2: returns false for out-of-range slot");
        Cargo* c3 = new StandardCargo(303, "Sprocket", 1.0);
        bool oob = lf.addCargo(c3, 99);
        CHECK(oob == false);
        delete c3;
    }

    SECTION("Empty vessel: getTotalWeight() == 0.0");
    {
        LightFreighter empty(6, "Ghost");
        CHECK_NEAR(empty.getTotalWeight(), 0.0, 0.001);
    }

    SECTION("totalVesselsCreated returns to 0 after all destroyed");
    CHECK_EQ(Vessel::getTotalVesselsCreated(), 0);

    SUMMARY();
}
