PROGRAMS = delta

CXXFLAGS ?= -Wall -Wextra -pedantic -O2
CXXFLAGS += -std=c++20

.PHONY: all clean

all: $(PROGRAMS)

%: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@
	strip $@

clean:
	rm -f $(PROGRAMS)
