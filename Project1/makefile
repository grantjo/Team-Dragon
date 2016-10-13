# compiler
CXX = g++

# compilation flags
CXXFLAGS = -std=c++11
CXXFLAGS += -g
CXXFLAGS += -pedantic-errors
CXXFLAGS += -Wall


#build all
all: enumeration better_enumeration divide_and_conquer linear_time

#buld individual
enumertion:  
	${CXX} ${CXXFLAGS} enumeration.cc -o enumeration
	
better_enumeration: 
	${CXX} ${CXXFLAGS} better_enumeration.cc -o better_enumeration
	
divide_and_conquer:
	${CXX} ${CXXFLAGS} -o divide_and_conquer.cc divide_and_conquer
	
linear_time:
	${CXX} ${CXXFLAGS} -o linear_time.cc linear_time
	
#prevent the creation of a clean file
.PHONY: clean

#remove all extraneous files such as .o and a.out files
clean:
	rm -rf *.o a.out
	

	
