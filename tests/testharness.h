// =============================================================
//  testharness.h  ---  Lightweight test framework for PA2
//  Include this header in every test file.
// =============================================================
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

// Internal counters (one per translation unit)
static int _th_passed = 0;
static int _th_failed = 0;
static int _th_total  = 0;

// ---- Colour codes (disable on Windows cmd by setting NO_COLOUR) ----
#ifndef NO_COLOUR
  #define _TH_GREEN  "\033[32m"
  #define _TH_RED    "\033[31m"
  #define _TH_YELLOW "\033[33m"
  #define _TH_CYAN   "\033[36m"
  #define _TH_RESET  "\033[0m"
#else
  #define _TH_GREEN  ""
  #define _TH_RED    ""
  #define _TH_YELLOW ""
  #define _TH_CYAN   ""
  #define _TH_RESET  ""
#endif

// ---- Section header ----
#define SECTION(name) \
    std::cout << "\n" _TH_CYAN "--- " name " ---" _TH_RESET "\n"

// ---- Basic boolean check ----
#define CHECK(cond) do { \
    ++_th_total; \
    if (cond) { \
        ++_th_passed; \
        std::cout << _TH_GREEN "  [PASS] " _TH_RESET #cond "\n"; \
    } else { \
        ++_th_failed; \
        std::cout << _TH_RED   "  [FAIL] " _TH_RESET #cond \
                  << "  (line " << __LINE__ << ")\n"; \
    } \
} while(0)

// ---- Equality check (prints actual vs expected on failure) ----
#define CHECK_EQ(actual, expected) do { \
    ++_th_total; \
    auto _a = (actual); \
    auto _e = (expected); \
    if (_a == _e) { \
        ++_th_passed; \
        std::cout << _TH_GREEN "  [PASS] " _TH_RESET \
                  << #actual << " == " << #expected << "\n"; \
    } else { \
        ++_th_failed; \
        std::cout << _TH_RED   "  [FAIL] " _TH_RESET \
                  << #actual << " == " << #expected \
                  << "  (got: " << _a << ", expected: " << _e \
                  << ")  line " << __LINE__ << "\n"; \
    } \
} while(0)

// ---- Floating-point equality (absolute tolerance) ----
#define CHECK_NEAR(actual, expected, tol) do { \
    ++_th_total; \
    double _a = (double)(actual); \
    double _e = (double)(expected); \
    if (std::abs(_a - _e) <= (double)(tol)) { \
        ++_th_passed; \
        std::cout << _TH_GREEN "  [PASS] " _TH_RESET \
                  << #actual << " ~= " << _e << "\n"; \
    } else { \
        ++_th_failed; \
        std::cout << _TH_RED   "  [FAIL] " _TH_RESET \
                  << #actual << " ~= " << _e \
                  << "  (got: " << _a << ")  line " << __LINE__ << "\n"; \
    } \
} while(0)

// ---- String contains sub-string ----
#define CHECK_CONTAINS(haystack, needle) do { \
    ++_th_total; \
    std::string _h = (haystack); \
    std::string _n = (needle); \
    if (_h.find(_n) != std::string::npos) { \
        ++_th_passed; \
        std::cout << _TH_GREEN "  [PASS] " _TH_RESET \
                  << "output contains \"" << _n << "\"\n"; \
    } else { \
        ++_th_failed; \
        std::cout << _TH_RED   "  [FAIL] " _TH_RESET \
                  << "output does not contain \"" << _n << "\"\n" \
                  << "         full output: [" << _h << "]\n" \
                  << "         line " << __LINE__ << "\n"; \
    } \
} while(0)

// ---- Null / non-null pointer checks ----
#define CHECK_NULL(ptr) do { \
    ++_th_total; \
    if ((ptr) == nullptr) { \
        ++_th_passed; \
        std::cout << _TH_GREEN "  [PASS] " _TH_RESET #ptr " is nullptr\n"; \
    } else { \
        ++_th_failed; \
        std::cout << _TH_RED   "  [FAIL] " _TH_RESET #ptr " should be nullptr\n" \
                  << "         line " << __LINE__ << "\n"; \
    } \
} while(0)

#define CHECK_NOT_NULL(ptr) do { \
    ++_th_total; \
    if ((ptr) != nullptr) { \
        ++_th_passed; \
        std::cout << _TH_GREEN "  [PASS] " _TH_RESET #ptr " is not nullptr\n"; \
    } else { \
        ++_th_failed; \
        std::cout << _TH_RED   "  [FAIL] " _TH_RESET #ptr " is nullptr (should not be)\n" \
                  << "         line " << __LINE__ << "\n"; \
    } \
} while(0)

// ---- Redirect std::cout to a string for output-format tests ----
// Usage:  CAPTURE_COUT(ss); obj.display(); std::string out = STOP_CAPTURE(ss);
#define CAPTURE_COUT(ss) \
    std::ostringstream ss; \
    std::streambuf* _saved_buf_##ss = std::cout.rdbuf(ss.rdbuf())

#define STOP_CAPTURE(ss) \
    [&]() -> std::string { \
        std::cout.rdbuf(_saved_buf_##ss); \
        return ss.str(); \
    }()

// ---- Final summary + return value ----
#define SUMMARY() do { \
    std::cout << "\n========================================\n"; \
    if (_th_failed == 0) { \
        std::cout << _TH_GREEN; \
    } else { \
        std::cout << _TH_RED; \
    } \
    std::cout << "Results: " << _th_passed << " / " << _th_total \
              << " passed    (" << _th_failed << " failed)" \
              << _TH_RESET "\n"; \
    std::cout << "========================================\n"; \
    return (_th_failed > 0) ? 1 : 0; \
} while(0)
