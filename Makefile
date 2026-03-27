# ================================================================
#  PA2 – Galactic Logistics Hub  |  Student Makefile
#  Compiler : g++ -std=c++11
#  Run from  : PA2/ root directory
# ================================================================

CXX      := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Iinclude -Itests

# ── Core library sources (shared by every target) ──────────────
SRCS := code/Entity.cpp \
        code/Cargo.cpp \
        code/StandardCargo.cpp \
        code/HazardousCargo.cpp \
        code/PerishableCargo.cpp \
        code/CargoLog.cpp \
        code/Vessel.cpp \
        code/LightFreighter.cpp \
        code/HeavyLifter.cpp \
        code/StealthRunner.cpp \
        code/Inspector.cpp \
        code/Hub.cpp

BINDIR := tests/bin

# ================================================================
#  Default target – run all visible tests with grade summary
# ================================================================
.PHONY: all
all: grade

# ================================================================
#  Visible tests –  t01 … t12
# ================================================================

define RUN_VIS
$(BINDIR)/$(1): $(SRCS) tests/visible/$(1).cpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $$@ tests/visible/$(1).cpp $(SRCS)

.PHONY: test-layer-$(2)
test-layer-$(2): $(BINDIR)/$(1)
	@echo ""; echo ">>> Running layer $(2): $(1)"; echo ""; ./$(BINDIR)/$(1)
endef

$(eval $(call RUN_VIS,t01_entity,01))
$(eval $(call RUN_VIS,t02_cargo_types,02))
$(eval $(call RUN_VIS,t03_vessel_base,03))
$(eval $(call RUN_VIS,t04_vessel_ruleof3,04))
$(eval $(call RUN_VIS,t05_derived_vessels,05))
$(eval $(call RUN_VIS,t06_inspector,06))
$(eval $(call RUN_VIS,t07_cargolog,07))
$(eval $(call RUN_VIS,t08_hub_basic,08))
$(eval $(call RUN_VIS,t09_hub_ruleof3,09))
$(eval $(call RUN_VIS,t10_fileio,10))
$(eval $(call RUN_VIS,t11_statics,11))
$(eval $(call RUN_VIS,t12_polymorphism,12))

# run all 12 layers then print weighted grade (alias for grade)
.PHONY: test-visible
test-visible: grade

# ================================================================
#  Grade summary – builds and reports each test progressively
# ================================================================
.PHONY: grade
grade: | $(BINDIR)
	@echo ""; \
	echo "====================================================="; \
	echo "  PA2 - Galactic Logistics Hub  |  Grade Report    "; \
	echo "====================================================="; \
	TOTAL=0; \
	pf() { \
	  label="$$1"; stem="$$2"; pts="$$3"; \
	  printf "  Building %-34s" "$$label"; \
	  if $(CXX) $(CXXFLAGS) -o $(BINDIR)/$$stem tests/visible/$$stem.cpp $(SRCS) 2>/dev/null; then \
	    if ./$(BINDIR)/$$stem >/dev/null 2>&1; then \
	      if [ "$$pts" -gt 0 ]; then \
	        printf "[PASS] %2d / %2d\n" $$pts $$pts; \
	        TOTAL=$$((TOTAL + $$pts)); \
	      else \
	        printf "[PASS]    ---\n"; \
	      fi; \
	    else \
	      if [ "$$pts" -gt 0 ]; then \
	        printf "[FAIL]  0 / %2d\n" $$pts; \
	      else \
	        printf "[FAIL]    ---\n"; \
	      fi; \
	    fi; \
	  else \
	    if [ "$$pts" -gt 0 ]; then \
	      printf "[ERR ]  0 / %2d\n" $$pts; \
	    else \
	      printf "[ERR ]    ---\n"; \
	    fi; \
	  fi; \
	}; \
	pf "t01  Abstraction (Entity)"           t01_entity          5; \
	pf "t02  Cargo types (integration)"      t02_cargo_types     0; \
	pf "t03  Encapsulation + Overloading"    t03_vessel_base     7; \
	pf "t04  Rule of Three - Vessel"         t04_vessel_ruleof3 10; \
	pf "t05  Inheritance & Polymorphism"     t05_derived_vessels 15; \
	pf "t06  Friend Class (Inspector)"       t06_inspector       7; \
	pf "t07  Linked List (CargoLog)"         t07_cargolog        4; \
	pf "t08  Function Overloading"           t08_hub_basic       2; \
	pf "t09  Rule of Three - Hub"            t09_hub_ruleof3     5; \
	pf "t10  File Handling"                  t10_fileio          8; \
	pf "t11  Static Members"                 t11_statics         7; \
	pf "t12  Polymorphism (integration)"     t12_polymorphism    0; \
	echo "-----------------------------------------------------"; \
	printf "  %-38s %2d / 70\n" "VISIBLE TOTAL" $$TOTAL; \
	echo "====================================================="; \
	echo "  Hidden tests (30 pts) graded by TA.               "; \
	echo "====================================================="; \
	echo ""

# ================================================================
#  Utility
# ================================================================
$(BINDIR):
	mkdir -p $(BINDIR)

.PHONY: clean
clean:
	rm -rf $(BINDIR)

.PHONY: help
help:
	@echo ""
	@echo "PA2 – Galactic Logistics Hub  |  Student Makefile"
	@echo "===================================================="
	@echo ""
	@echo "  make                 Build all + weighted grade summary (default)"
	@echo "  make grade           Same as above"
	@echo "  make test-visible    Same as above"
	@echo ""
	@echo "  --- Debug layer by layer (stops on first failure) ---"
	@echo "  make test-layer-01   Entity (abstraction / ID counter)"
	@echo "  make test-layer-02   Cargo types & effective weights"
	@echo "  make test-layer-03   Vessel base class & addCargo overloads"
	@echo "  make test-layer-04   Vessel Rule of Three"
	@echo "  make test-layer-05   Derived vessels & fuel formulas"
	@echo "  make test-layer-06   Inspector (friend class)"
	@echo "  make test-layer-07   CargoLog linked list node"
	@echo "  make test-layer-08   Hub basic operations"
	@echo "  make test-layer-09   Hub Rule of Three"
	@echo "  make test-layer-10   File I/O (loadFleet / saveReport)"
	@echo "  make test-layer-11   Static member counters"
	@echo "  make test-layer-12   Polymorphism via base pointers"
	@echo ""
	@echo "  make test-visible    Run all 12 visible tests in order"
	@echo ""
	@echo "  --- Utility ---"
	@echo "  make clean           Remove tests/bin/ directory"
	@echo "  make help            Show this message"
	@echo ""
