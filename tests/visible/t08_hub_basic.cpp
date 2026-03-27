// =============================================================
//  T08 --- Hub basic: addVessel, findVessel overloads,
//          processLogistics, printLog
// =============================================================
#include "../testharness.h"
#include "../../include/Hub.h"
#include "../../include/LightFreighter.h"
#include "../../include/HeavyLifter.h"
#include "../../include/StealthRunner.h"
#include "../../include/StandardCargo.h"

int main() {
    std::cout << "========================================\n";
    std::cout << "  Layer 08 --- Hub Basic\n";
    std::cout << "========================================\n";

    SECTION("Hub constructor: empty hub, 20 dock slots");
    {
        Hub h;
        // We test via findVessel returning nullptr for any lookup
        CHECK_NULL(h.findVessel("NoSuchShip"));
        CHECK_NULL(h.findVessel(0));
    }

    SECTION("addVessel: vessels retrievable via findVessel(name)");
    {
        Hub h;
        h.addVessel(new LightFreighter(1, "Firefly"));
        h.addVessel(new HeavyLifter  (2, "Goliath"));
        h.addVessel(new StealthRunner(3, "Phantom", 0.75));

        Vessel* v1 = h.findVessel("Firefly");
        Vessel* v2 = h.findVessel("Goliath");
        Vessel* v3 = h.findVessel("Phantom");

        CHECK_NOT_NULL(v1);
        CHECK_NOT_NULL(v2);
        CHECK_NOT_NULL(v3);
        CHECK_EQ(v1->getName(), std::string("Firefly"));
        CHECK_EQ(v2->getName(), std::string("Goliath"));
        CHECK_EQ(v3->getName(), std::string("Phantom"));
    }

    SECTION("findVessel(name): returns nullptr for unknown name");
    {
        Hub h;
        h.addVessel(new LightFreighter(1, "Firefly"));
        CHECK_NULL(h.findVessel("Ghost"));
    }

    SECTION("findVessel(int): returns vessel by zero-based index");
    {
        Hub h;
        h.addVessel(new LightFreighter(1, "Firefly"));
        h.addVessel(new HeavyLifter  (2, "Goliath"));

        Vessel* v0 = h.findVessel(0);
        Vessel* v1 = h.findVessel(1);
        CHECK_NOT_NULL(v0);
        CHECK_NOT_NULL(v1);
        CHECK_EQ(v0->getName(), std::string("Firefly"));
        CHECK_EQ(v1->getName(), std::string("Goliath"));
    }

    SECTION("findVessel(int): returns nullptr for out-of-range index");
    {
        Hub h;
        h.addVessel(new LightFreighter(1, "Firefly"));
        CHECK_NULL(h.findVessel(5));
        CHECK_NULL(h.findVessel(-1));
    }

    SECTION("addVessel: dock-full message when capacity exceeded");
    {
        Hub h;
        // Fill all 20 slots
        for (int i = 0; i < 20; i++) {
            h.addVessel(new LightFreighter(i, "Ship" + std::to_string(i)));
        }
        CAPTURE_COUT(ss);
        Vessel* extra = new LightFreighter(99, "Extra");
        h.addVessel(extra);
        std::string out = STOP_CAPTURE(ss);
        CHECK_CONTAINS(out, "full");
        // extra not stored; student must delete it — we skip delete to test message only
        // (minor intentional leak in test only)
    }

    SECTION("processLogistics: calls display() on every vessel");
    {
        Hub h;
        h.addVessel(new LightFreighter(1, "Alpha"));
        h.addVessel(new HeavyLifter  (2, "Beta"));

        CAPTURE_COUT(ss);
        h.processLogistics();
        std::string out = STOP_CAPTURE(ss);

        CHECK_CONTAINS(out, "Alpha");
        CHECK_CONTAINS(out, "Beta");
        CHECK_CONTAINS(out, "LightFreighter");
        CHECK_CONTAINS(out, "HeavyLifter");
    }

    SECTION("printLog: empty hub prints no-entries message");
    {
        Hub h;
        CAPTURE_COUT(ss);
        h.printLog();
        std::string out = STOP_CAPTURE(ss);
        CHECK_CONTAINS(out, "No cargo log");
    }

    SECTION("printLog: after loadFleet, log entries present");
    {
        Hub h;
        h.loadFleet("fleet.txt");
        CAPTURE_COUT(ss);
        h.printLog();
        std::string out = STOP_CAPTURE(ss);
        CHECK_CONTAINS(out, "[LOG]");
        CHECK_CONTAINS(out, "loaded onto");
    }

    SUMMARY();
}
