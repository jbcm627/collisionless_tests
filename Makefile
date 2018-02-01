
include Makefile.inc

CXXFLAGS += -std=c++11

LDLIBS += -lfftw3_omp
LDLIBS += -lfftw3
LDLIBS += -lz

# Comment this out if you are using the Intel compiler (`icpc`).
LDLIBS += -lm

EXE = collisionless_tests

all: main.cc *.h
	$(CXX) main.cc -o $(EXE) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(EXE)
