// =============================================================
//  T07 --- CargoLog: singly-linked list construction and traversal
// =============================================================
#include "../testharness.h"
#include "../../include/CargoLog.h"

int main() {
    std::cout << "========================================\n";
    std::cout << "  Layer 07 --- CargoLog Linked List\n";
    std::cout << "========================================\n";

    SECTION("CargoLog constructor: fields set, next == nullptr");
    {
        CargoLog node("FoodSupplies", "Firefly");
        CHECK_EQ(node.cargoDescription, std::string("FoodSupplies"));
        CHECK_EQ(node.vesselName,       std::string("Firefly"));
        CHECK_NULL(node.next);
    }

    SECTION("Manual linked list: three nodes, correct chain");
    {
        CargoLog* n1 = new CargoLog("FoodSupplies", "Firefly");
        CargoLog* n2 = new CargoLog("Uranium",      "Firefly");
        CargoLog* n3 = new CargoLog("Vaccines",     "Firefly");

        n1->next = n2;
        n2->next = n3;
        // n3->next == nullptr already

        CHECK_EQ(n1->cargoDescription, std::string("FoodSupplies"));
        CHECK_EQ(n1->next->cargoDescription, std::string("Uranium"));
        CHECK_EQ(n1->next->next->cargoDescription, std::string("Vaccines"));
        CHECK_NULL(n1->next->next->next);

        SECTION("Traversal reaches every node");
        int count = 0;
        for (CargoLog* cur = n1; cur != nullptr; cur = cur->next) {
            ++count;
        }
        CHECK_EQ(count, 3);

        // Free manually
        delete n3;
        delete n2;
        delete n1;
    }

    SECTION("Single-node list: next is nullptr");
    {
        CargoLog* sole = new CargoLog("DataCores", "Phantom");
        CHECK_NULL(sole->next);
        delete sole;
    }

    SUMMARY();
}
