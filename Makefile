PROGRAMS = delta

CC = c++
CFLAGS=-Wall -O2 -std=c++17
LIBS=-lboost_date_time

all: $(PROGRAMS)

.cc: ; $(CC) $(CFLAGS) $@.cc $(LIBS) -o $@
	strip $@

clean:
	rm $(PROGRAMS)
