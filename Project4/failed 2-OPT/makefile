# the compiler: gcc for C program, define as g++ for C++
CXX = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CXXFLAGS  = -g -static -Wall -std=c++11

# the build target executable:
PROGS = tsp
OBJS = Source.o tsp.o city.o

.PHONY: all clean

all: $(PROGS)

$(PROGS): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o tsp

Source.o: Source.cpp tsp.h
	$(CXX) $(CXXFLAGS) -c Source.cpp

tsp.o: tsp.cpp tsp.h
	$(CXX) $(CXXFLAGS) -c tsp.cpp

city.o: city.cpp city.h
	$(CXX) $(CXXFLAGS) -c city.cpp

clean:  
	rm -f *.exe *.o *~ tsp