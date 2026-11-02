PROGRAMS = delta
TESTS = delta_test

CXXFLAGS ?= -Wall -Wextra -pedantic -O2
override CXXFLAGS += -std=c++20

.PHONY: all test clean

all: $(PROGRAMS)

delta: delta.cc delta.h
	$(CXX) $(CXXFLAGS) $< -o $@
	strip $@

delta_test: delta_test.cc delta.h
	$(CXX) $(CXXFLAGS) $< -o $@

test: $(TESTS)
	./delta_test

clean:
	rm -f $(PROGRAMS) $(TESTS)
