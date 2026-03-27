// =============================================================
//  T02 --- Cargo types: effective weights, clone, static counter
// =============================================================
#include "../testharness.h"
#include "../../include/StandardCargo.h"
#include "../../include/HazardousCargo.h"
#include "../../include/PerishableCargo.h"
#include <sstream>

int main() {
    std::cout << "========================================\n";
    std::cout << "  Layer 02 --- Cargo Types\n";
    std::cout << "========================================\n";

    SECTION("totalCargoCreated starts at 0");
    CHECK_EQ(Cargo::getTotalCargoCreated(), 0);

    // ---- StandardCargo ----
    SECTION("StandardCargo: effective weight == raw weight");
    {
        StandardCargo sc(1, "FoodSupplies", 10.0);
        CHECK_NEAR(sc.getEffectiveWeight(), 10.0, 0.001);
        CHECK_NEAR(sc.getWeight(),          10.0, 0.001);
        CHECK_EQ(sc.getDescription(), std::string("FoodSupplies"));
        CHECK_EQ(sc.getID(), 1);
        CHECK_EQ(Cargo::getTotalCargoCreated(), 1);

        SECTION("StandardCargo: display contains expected tokens");
        CAPTURE_COUT(ss1);
        sc.display();
        std::string out1 = STOP_CAPTURE(ss1);
        CHECK_CONTAINS(out1, "FoodSupplies");
        CHECK_CONTAINS(out1, "Standard");
        CHECK_CONTAINS(out1, "10.00");
    }
    CHECK_EQ(Cargo::getTotalCargoCreated(), 0);

    // ---- HazardousCargo ----
    SECTION("HazardousCargo overload 1: hazardLevel defaults to 1");
    {
        HazardousCargo hc1(2, "Uranium", 5.0);
        CHECK_EQ(hc1.getHazardLevel(), 1);
        CHECK_NEAR(hc1.getEffectiveWeight(), 6.0, 0.001);   // 5.0 * 1.2
    }

    SECTION("HazardousCargo overload 2: custom hazardLevel");
    {
        HazardousCargo hc2(3, "Acids", 8.0, 3);
        CHECK_EQ(hc2.getHazardLevel(), 3);
        CHECK_NEAR(hc2.getEffectiveWeight(), 9.6, 0.001);   // 8.0 * 1.2

        SECTION("HazardousCargo: display contains expected tokens");
        CAPTURE_COUT(ss2);
        hc2.display();
        std::string out2 = STOP_CAPTURE(ss2);
        CHECK_CONTAINS(out2, "Acids");
        CHECK_CONTAINS(out2, "Hazardous");
        CHECK_CONTAINS(out2, "Level: 3");
    }

    SECTION("HazardousCargo: hazardLevel clamped to [1,5]");
    {
        HazardousCargo hcLow(4, "X", 1.0, 0);   // below range
        CHECK_EQ(hcLow.getHazardLevel(), 1);

        HazardousCargo hcHigh(5, "Y", 1.0, 9);  // above range
        CHECK_EQ(hcHigh.getHazardLevel(), 5);
    }

    // ---- PerishableCargo ----
    SECTION("PerishableCargo: effective weight = raw + 5.0");
    {
        PerishableCargo pc(6, "Vaccines", 2.0, 7);
        CHECK_NEAR(pc.getEffectiveWeight(), 7.0, 0.001);    // 2.0 + 5.0
        CHECK_EQ(pc.getExpiryDays(), 7);

        SECTION("PerishableCargo: display contains expected tokens");
        CAPTURE_COUT(ss3);
        pc.display();
        std::string out3 = STOP_CAPTURE(ss3);
        CHECK_CONTAINS(out3, "Vaccines");
        CHECK_CONTAINS(out3, "Perishable");
        CHECK_CONTAINS(out3, "7");    // expiry days
    }

    SECTION("PerishableCargo: expiryDays <= 0 clamped to 1");
    {
        // stderr warning expected; we only verify the clamped value
        PerishableCargo pc2(7, "BioSamples", 1.0, 0);
        CHECK_EQ(pc2.getExpiryDays(), 1);
    }

    // ---- clone() ----
    SECTION("clone() returns non-null and correct derived type");
    {
        StandardCargo  sc(8, "A", 5.0);
        HazardousCargo hc(9, "B", 3.0, 2);
        PerishableCargo pc(10, "C", 1.0, 5);

        Cargo* cs = sc.clone();
        Cargo* ch = hc.clone();
        Cargo* cp = pc.clone();

        CHECK_NOT_NULL(cs);
        CHECK_NOT_NULL(ch);
        CHECK_NOT_NULL(cp);

        CHECK_NEAR(cs->getEffectiveWeight(), 5.0,  0.001);
        CHECK_NEAR(ch->getEffectiveWeight(), 3.6,  0.001);   // 3.0 * 1.2
        CHECK_NEAR(cp->getEffectiveWeight(), 6.0,  0.001);   // 1.0 + 5.0

        SECTION("clone() creates independent copy");
        CHECK(cs != (Cargo*)&sc);   // different address

        delete cs; delete ch; delete cp;
    }

    SECTION("totalCargoCreated returns to 0 after all destroyed");
    CHECK_EQ(Cargo::getTotalCargoCreated(), 0);

    SUMMARY();
}
