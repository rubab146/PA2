// =============================================================
//  T06 --- Inspector: friend access, inspect(), countNullSlots()
// =============================================================
#include "../testharness.h"
#include "../../include/LightFreighter.h"
#include "../../include/HeavyLifter.h"
#include "../../include/StandardCargo.h"
#include "../../include/Inspector.h"

int main() {
    std::cout << "========================================\n";
    std::cout << "  Layer 06 --- Inspector (Friend Class)\n";
    std::cout << "========================================\n";

    Inspector insp;

    // ---- countNullSlots on empty vessel ----
    SECTION("countNullSlots: fully empty vessel = maxCapacity null slots");
    {
        LightFreighter empty(1, "Ghost");
        int nulls = insp.countNullSlots(empty);
        CHECK_EQ(nulls, 10);   // default capacity
    }

    SECTION("countNullSlots: partially loaded vessel");
    {
        LightFreighter lf(2, "Firefly");
        lf.addCargo(new StandardCargo(101, "ItemA", 5.0));
        lf.addCargo(new StandardCargo(102, "ItemB", 3.0));
        // 2 loaded, 8 empty out of 10
        int nulls = insp.countNullSlots(lf);
        CHECK_EQ(nulls, 8);
    }

    SECTION("countNullSlots: fully loaded vessel = 0 null slots");
    {
        LightFreighter small(3, "Packed", 3);
        small.addCargo(new StandardCargo(201, "A", 1.0));
        small.addCargo(new StandardCargo(202, "B", 1.0));
        small.addCargo(new StandardCargo(203, "C", 1.0));
        int nulls = insp.countNullSlots(small);
        CHECK_EQ(nulls, 0);
    }

    // ---- inspect() output format ----
    SECTION("inspect(): output contains vessel name");
    {
        LightFreighter lf(4, "Firefly");
        lf.addCargo(new StandardCargo(301, "FoodSupplies", 10.0));

        CAPTURE_COUT(ss);
        insp.inspect(lf);
        std::string out = STOP_CAPTURE(ss);

        CHECK_CONTAINS(out, "Firefly");
        CHECK_CONTAINS(out, "Manifest");
    }

    SECTION("inspect(): output contains cargo description and effective weight");
    {
        LightFreighter lf(5, "Ship");
        lf.addCargo(new StandardCargo(401, "Ore", 8.0));

        CAPTURE_COUT(ss);
        insp.inspect(lf);
        std::string out = STOP_CAPTURE(ss);

        CHECK_CONTAINS(out, "Ore");
        CHECK_CONTAINS(out, "8.00");     // effective weight
    }

    SECTION("inspect(): empty slots appear as (empty)");
    {
        LightFreighter lf(6, "Sparse", 3);
        lf.addCargo(new StandardCargo(501, "Widget", 2.0));
        // slots 1 and 2 are empty

        CAPTURE_COUT(ss);
        insp.inspect(lf);
        std::string out = STOP_CAPTURE(ss);

        CHECK_CONTAINS(out, "(empty)");
    }

    SECTION("inspect(): capacity line is present");
    {
        HeavyLifter hl(7, "Titan", 5);
        hl.addCargo(new StandardCargo(601, "Rock", 20.0));

        CAPTURE_COUT(ss);
        insp.inspect(hl);
        std::string out = STOP_CAPTURE(ss);

        CHECK_CONTAINS(out, "Capacity");
        CHECK_CONTAINS(out, "1");   // currentLoad
        CHECK_CONTAINS(out, "5");   // maxCapacity
    }

    SUMMARY();
}
