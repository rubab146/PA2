// =============================================================
//  T05 --- Derived Vessels: fuel formulas, display format, clone
// =============================================================
#include "../testharness.h"
#include "../../include/LightFreighter.h"
#include "../../include/HeavyLifter.h"
#include "../../include/StealthRunner.h"
#include "../../include/StandardCargo.h"
#include "../../include/HazardousCargo.h"
#include "../../include/PerishableCargo.h"

// Load the three vessels matching the spec sample
static void loadFirefly(LightFreighter& lf) {
    lf.addCargo(new StandardCargo(101, "FoodSupplies", 10.0));
    lf.addCargo(new HazardousCargo(102, "Uranium",      5.0, 3));
    lf.addCargo(new PerishableCargo(103, "Vaccines",    2.0, 7));
    // effective weights: 10.0, 6.0, 7.0  => total 23.0
}

static void loadGoliath(HeavyLifter& hl) {
    hl.addCargo(new StandardCargo(201, "MachinePartsA", 40.0));
    hl.addCargo(new StandardCargo(202, "MachinePartsB", 35.0));
    hl.addCargo(new HazardousCargo(203, "Acids",         8.0, 1));
    // effective weights: 40.0, 35.0, 9.6  => total 84.6
}

static void loadPhantom(StealthRunner& sr) {
    sr.addCargo(new PerishableCargo(301, "BioSamples", 1.5, 3));
    sr.addCargo(new StandardCargo(302, "DataCores",    0.5));
    // effective weights: 6.5, 0.5  => total 7.0
}

int main() {
    std::cout << "========================================\n";
    std::cout << "  Layer 05 --- Derived Vessels\n";
    std::cout << "========================================\n";

    // ---- LightFreighter ----
    SECTION("LightFreighter: fuel = distance * totalWeight * 0.5");
    {
        LightFreighter lf(1, "Firefly");
        loadFirefly(lf);
        CHECK_NEAR(lf.getTotalWeight(),       23.0,    0.001);
        CHECK_NEAR(lf.calculateFuel(100),   1150.0,    0.1);   // 100*23*0.5
    }

    SECTION("LightFreighter: display contains required tokens");
    {
        LightFreighter lf(1, "Firefly");
        loadFirefly(lf);
        CAPTURE_COUT(ss);
        lf.display();
        std::string out = STOP_CAPTURE(ss);
        CHECK_CONTAINS(out, "Firefly");
        CHECK_CONTAINS(out, "LightFreighter");
        CHECK_CONTAINS(out, "3 / 10");          // cargo count / capacity
        CHECK_CONTAINS(out, "23.00");           // total effective weight
        // 42-dash separator
        CHECK_CONTAINS(out, "------------------------------------------");
    }

    // ---- HeavyLifter ----
    SECTION("HeavyLifter: fuel = (distance * totalWeight * 1.5) + 500");
    {
        HeavyLifter hl(2, "Goliath");
        loadGoliath(hl);
        CHECK_NEAR(hl.getTotalWeight(), 84.6, 0.01);
        // 100 * 84.6 * 1.5 + 500 = 12690 + 500 = 13190
        CHECK_NEAR(hl.calculateFuel(100), 13190.0, 1.0);
    }

    SECTION("HeavyLifter: display contains required tokens");
    {
        HeavyLifter hl(2, "Goliath");
        loadGoliath(hl);
        CAPTURE_COUT(ss);
        hl.display();
        std::string out = STOP_CAPTURE(ss);
        CHECK_CONTAINS(out, "Goliath");
        CHECK_CONTAINS(out, "HeavyLifter");
        CHECK_CONTAINS(out, "84.60");
    }

    // ---- StealthRunner ----
    SECTION("StealthRunner: fuel = distance * totalWeight * cloakRating");
    {
        StealthRunner sr(3, "Phantom", 0.75);
        loadPhantom(sr);
        CHECK_NEAR(sr.getTotalWeight(),     7.0,   0.001);
        CHECK_NEAR(sr.getCloakRating(),    0.75,   0.001);
        // 100 * 7.0 * 0.75 = 525
        CHECK_NEAR(sr.calculateFuel(100), 525.0,   0.1);
    }

    SECTION("StealthRunner: cloakRating clamped to [0.0, 1.0]");
    {
        StealthRunner srLow(4, "Low",  -0.5);
        CHECK_NEAR(srLow.getCloakRating(), 0.0, 0.001);

        StealthRunner srHigh(5, "High",  2.5);
        CHECK_NEAR(srHigh.getCloakRating(), 1.0, 0.001);
    }

    SECTION("StealthRunner: display contains CloakRating token");
    {
        StealthRunner sr(6, "Phantom", 0.75);
        CAPTURE_COUT(ss);
        sr.display();
        std::string out = STOP_CAPTURE(ss);
        CHECK_CONTAINS(out, "StealthRunner");
        CHECK_CONTAINS(out, "CloakRating");
        CHECK_CONTAINS(out, "0.75");
    }

    // ---- Polymorphic clone ----
    SECTION("clone() via base pointer returns correct derived type");
    {
        LightFreighter lf(7, "CloneMe");
        lf.addCargo(new StandardCargo(401, "X", 5.0));

        Vessel* copy = lf.clone();
        CHECK_NOT_NULL(copy);
        CHECK_NEAR(copy->getTotalWeight(), 5.0, 0.001);
        CHECK_NEAR(copy->calculateFuel(10),
                   lf.calculateFuel(10), 0.001);
        delete copy;
    }

    // ---- Custom capacity constructors ----
    SECTION("Constructor overload 2: custom capacity works for all types");
    {
        LightFreighter lf(8, "A", 3);
        HeavyLifter    hl(9, "B", 7);
        StealthRunner  sr(10, "C", 4, 0.5);
        CHECK_EQ(lf.getMaxCapacity(), 3);
        CHECK_EQ(hl.getMaxCapacity(), 7);
        CHECK_EQ(sr.getMaxCapacity(), 4);
    }

    SUMMARY();
}
