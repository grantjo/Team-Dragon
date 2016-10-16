# compiler
CXX = g++

# compilation flags
CXXFLAGS = -std=c++11
CXXFLAGS += -g
CXXFLAGS += -pedantic-errors
CXXFLAGS += -Wall


#build all
all: enumeration better_enumeration divide_and_conquer linear_time random

#buld individual
enumeration:  
	${CXX} ${CXXFLAGS} enumeration.cc -o enumeration
	
better_enumeration: 
	${CXX} ${CXXFLAGS} better_enumeration.cc -o better_enumeration
	
divide_and_conquer:
	${CXX} ${CXXFLAGS} divide_and_conquer.cc -o divide_and_conquer
	
linear_time:
	${CXX} ${CXXFLAGS} linear_time.cc -o linear_time

random:
	${CXX} ${CXXFLAGS} random.cc -o random
	
# Typing 'make clean' calls this build.
# It's designed to clean up the folder.
# Be careful with this, edit as needed.
clean: 
	rm -f ${PROGS}  *.o *~ a.out
	
# Only needed in Windows where the .exe extension is appended
# to executables. Rather than rm -f *.exe, this leaves in
# place any other executables that might be present.
rmexes:
	rm -f enumeration.exe
	rm -f better_enumeration.exe
	rm -f divide_and_conquer.exe
	rm -f linear_time.exe
	rm -f random.exe
	

	
