// =============================================================
//  T09 --- Hub Rule of Three: deep copy, self-assignment,
//          log list copied independently
// =============================================================
#include "../testharness.h"
#include "../../include/Hub.h"
#include "../../include/LightFreighter.h"
#include "../../include/HeavyLifter.h"
#include "../../include/StealthRunner.h"

int main() {
    std::cout << "========================================\n";
    std::cout << "  Layer 09 --- Hub Rule of Three\n";
    std::cout << "========================================\n";

    // Build a non-trivial hub from fleet.txt
    SECTION("Hub copy constructor: vessels accessible in copy");
    {
        Hub orig;
        orig.loadFleet("fleet.txt");

        Hub copy(orig);

        // Both hubs should have same vessels resolvable by name
        CHECK_NOT_NULL(copy.findVessel("Firefly"));
        CHECK_NOT_NULL(copy.findVessel("Goliath"));
        CHECK_NOT_NULL(copy.findVessel("Phantom"));
    }

    SECTION("Hub copy constructor: copy is independent of original");
    {
        Hub orig;
        orig.loadFleet("fleet.txt");

        Hub copy(orig);

        // Add a new vessel only to orig; copy must not see it
        orig.addVessel(new LightFreighter(99, "NewShip"));

        CHECK_NOT_NULL(orig.findVessel("NewShip"));
        CHECK_NULL(copy.findVessel("NewShip"));
    }

    SECTION("Hub copy constructor: deleting original does not corrupt copy");
    {
        Hub* orig = new Hub();
        orig->loadFleet("fleet.txt");

        Hub copy(*orig);
        delete orig;   // orig destroyed; copy must remain valid

        CAPTURE_COUT(ss);
        copy.processLogistics();
        std::string out = STOP_CAPTURE(ss);

        CHECK_CONTAINS(out, "Firefly");
        CHECK_CONTAINS(out, "Goliath");
        CHECK_CONTAINS(out, "Phantom");
    }

    SECTION("Hub copy constructor: log is deep-copied");
    {
        Hub orig;
        orig.loadFleet("fleet.txt");

        Hub copy(orig);

        CAPTURE_COUT(ss1);
        orig.printLog();
        std::string logOrig = STOP_CAPTURE(ss1);

        CAPTURE_COUT(ss2);
        copy.printLog();
        std::string logCopy = STOP_CAPTURE(ss2);

        // Both should contain the same log entries
        CHECK_CONTAINS(logCopy, "FoodSupplies");
        CHECK_CONTAINS(logCopy, "Firefly");
    }

    SECTION("Hub copy assignment operator: independent copy");
    {
        Hub src;
        src.loadFleet("fleet.txt");

        Hub dst;
        dst = src;

        CHECK_NOT_NULL(dst.findVessel("Phantom"));

        src.addVessel(new StealthRunner(88, "Ghost", 0.3));
        CHECK_NOT_NULL(src.findVessel("Ghost"));
        CHECK_NULL(dst.findVessel("Ghost"));
    }

    SECTION("Hub copy assignment operator: re-assignment to existing hub");
    {
        Hub hub1;
        hub1.addVessel(new LightFreighter(1, "Alpha"));

        Hub hub2;
        hub2.addVessel(new HeavyLifter(2, "Beta"));

        hub2 = hub1;   // hub2 should lose Beta and gain Alpha

        CHECK_NOT_NULL(hub2.findVessel("Alpha"));
        CHECK_NULL(hub2.findVessel("Beta"));
    }

    SECTION("Hub self-assignment: does not crash or corrupt");
    {
        Hub h;
        h.loadFleet("fleet.txt");

        h = h;   // self-assignment — must not crash or lose data

        CHECK_NOT_NULL(h.findVessel("Firefly"));
        CHECK_NOT_NULL(h.findVessel("Goliath"));
    }

    SECTION("Static counters return to 0 after all Hubs destroyed");
    CHECK_EQ(Entity::getEntityCount(), 0);
    CHECK_EQ(Cargo::getTotalCargoCreated(), 0);
    CHECK_EQ(Vessel::getTotalVesselsCreated(), 0);

    SUMMARY();
}
