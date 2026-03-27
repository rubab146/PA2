// =============================================================
//  T10 --- File I/O: loadFleet(), saveReport()
// =============================================================
#include "../testharness.h"
#include "../../include/Hub.h"
#include <fstream>
#include <sstream>

// Read an entire file into a string
static std::string readFile(const std::string& path) {
    std::ifstream f(path);
    if (!f.is_open()) return "";
    std::ostringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

int main() {
    std::cout << "========================================\n";
    std::cout << "  Layer 10 --- File I/O\n";
    std::cout << "========================================\n";

    // ---- loadFleet ----
    SECTION("loadFleet: opens fleet.txt without error");
    {
        Hub h;
        CAPTURE_COUT(ss);
        h.loadFleet("fleet.txt");
        std::string out = STOP_CAPTURE(ss);
        // Error message must NOT appear
        CHECK(out.find("Error opening") == std::string::npos);
    }

    SECTION("loadFleet: correct number of vessels (3)");
    {
        Hub h;
        h.loadFleet("fleet.txt");
        CHECK_NOT_NULL(h.findVessel("Firefly"));
        CHECK_NOT_NULL(h.findVessel("Goliath"));
        CHECK_NOT_NULL(h.findVessel("Phantom"));
    }

    SECTION("loadFleet: vessel types resolved correctly");
    {
        Hub h;
        h.loadFleet("fleet.txt");

        Vessel* lf = h.findVessel("Firefly");
        Vessel* hl = h.findVessel("Goliath");

        CHECK_NOT_NULL(lf);
        CHECK_NOT_NULL(hl);

        CAPTURE_COUT(s1);
        if (lf) lf->display();
        std::string o1 = STOP_CAPTURE(s1);
        CHECK_CONTAINS(o1, "LightFreighter");

        CAPTURE_COUT(s2);
        if (hl) hl->display();
        std::string o2 = STOP_CAPTURE(s2);
        CHECK_CONTAINS(o2, "HeavyLifter");
    }

    SECTION("loadFleet: cargo counts correct");
    {
        Hub h;
        h.loadFleet("fleet.txt");

        Vessel* lf = h.findVessel("Firefly");   // 3 cargo items
        Vessel* hl = h.findVessel("Goliath");   // 3 cargo items
        Vessel* sr = h.findVessel("Phantom");   // 2 cargo items

        if (lf) CHECK_EQ(lf->getCurrentLoad(), 3);
        if (hl) CHECK_EQ(hl->getCurrentLoad(), 3);
        if (sr) CHECK_EQ(sr->getCurrentLoad(), 2);
    }

    SECTION("loadFleet: effective weights computed correctly after parse");
    {
        Hub h;
        h.loadFleet("fleet.txt");

        Vessel* lf = h.findVessel("Firefly");
        Vessel* hl = h.findVessel("Goliath");
        Vessel* sr = h.findVessel("Phantom");

        if (lf) CHECK_NEAR(lf->getTotalWeight(), 23.0,  0.01);
        if (hl) CHECK_NEAR(hl->getTotalWeight(), 84.6,  0.1);
        if (sr) CHECK_NEAR(sr->getTotalWeight(),  7.0,  0.01);
    }

    SECTION("loadFleet: bad filename prints error message");
    {
        Hub h;
        CAPTURE_COUT(ss);
        h.loadFleet("nonexistent_file_xyz.txt");
        std::string out = STOP_CAPTURE(ss);
        CHECK_CONTAINS(out, "Error opening file");
    }

    // ---- saveReport ----
    SECTION("saveReport: creates report.txt");
    {
        Hub h;
        h.loadFleet("fleet.txt");
        h.saveReport("tests/report_test_out.txt");

        std::string content = readFile("tests/report_test_out.txt");
        CHECK(content.size() > 0);
    }

    SECTION("saveReport: report contains header line");
    {
        std::string content = readFile("tests/report_test_out.txt");
        CHECK_CONTAINS(content, "Galactic Logistics Hub Report");
    }

    SECTION("saveReport: report contains all three vessel names");
    {
        std::string content = readFile("tests/report_test_out.txt");
        CHECK_CONTAINS(content, "Firefly");
        CHECK_CONTAINS(content, "Goliath");
        CHECK_CONTAINS(content, "Phantom");
    }

    SECTION("saveReport: report contains cargo log section");
    {
        std::string content = readFile("tests/report_test_out.txt");
        CHECK_CONTAINS(content, "Cargo Load Log");
        CHECK_CONTAINS(content, "[LOG]");
        CHECK_CONTAINS(content, "loaded onto");
    }

    SECTION("saveReport: key numeric values correct (Firefly weight)");
    {
        std::string content = readFile("tests/report_test_out.txt");
        CHECK_CONTAINS(content, "23.00");    // Firefly total effective weight
    }

    SECTION("saveReport: 42-dash separator lines present");
    {
        std::string content = readFile("tests/report_test_out.txt");
        CHECK_CONTAINS(content, "------------------------------------------");
    }

    SUMMARY();
}
