###############################################################################
#  University of Hawaii, College of Engineering
#  Lab D - Lucky Cat - EE 205 (Object Oriented Programming) - Spr 2024
#
#  Cats make their own luck
#
## A lottery simulation
##
## @see     https://www.gnu.org/software/make/manual/make.html
##
## @file   Makefile
## @author Mark Nelson <marknels@hawaii.edu>
###############################################################################

TARGET = sim

all: $(TARGET)

CC        = clang++
CFLAGS    = -Wall -Wextra -Werror -march=native -mtune=native -masm=intel $(DEBUG_FLAGS)
LINT      = clang-tidy
LINTFLAGS = --quiet

debug: DEBUG_FLAGS = -g3 -ggdb -DDEBUG -O0
debug: clean $(TARGET)

test:     CFLAGS += -DTESTING

valgrind: CFLAGS += -DTESTING -g -O0 -fno-inline -march=x86-64 -mtune=generic

Game.o: Game.cpp Game.h
	$(CC) $(CFLAGS) -c $<

Draw.o: Draw.cpp Draw.h
	$(CC) $(CFLAGS) -c $<

Sim.o: Sim.cpp
	$(CC) $(CFLAGS) -c $<

$(TARGET): Game.o Draw.o Sim.o
	$(CC) $(CFLAGS) -o $(TARGET) $^

lint:
	$(LINT) $(LINTFLAGS) Game.cpp Draw.cpp Sim.cpp --

doc: $(TARGET)
	./.doxygen/stats.py
	rsync --recursive --mkpath --checksum --delete --compress --stats --chmod=o+r,Do+x .doxygen/images .doxygen/docs/html/.doxygen
	doxygen .doxygen/Doxyfile

publish: doc
	rsync --recursive --checksum --delete --compress --stats --chmod=o+r,Do+x .doxygen/docs/html/ marknels@uhunix.hawaii.edu:~/public_html/ee205/ee205_labF_cat_luck

test: $(TARGET)
	cd tests ; $(MAKE) test

test_valgrind: $(TARGET)
	cd tests ; $(MAKE) valgrind

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	DEBUGINFOD_URLS="https://debuginfod.archlinux.org" \
	valgrind --leak-check=full    \
	         --track-origins=yes  \
	         --error-exitcode=1   \
	         --quiet              \
	./$(TARGET)

clean:
	rm -fr $(TARGET) *.o .doxygen/docs
	cd tests ; $(MAKE) clean
