# compiler
CXX = g++

# compilation flags
CXXFLAGS = -std=c++11
CXXFLAGS += -g
CXXFLAGS += -pedantic-errors
CXXFLAGS += -Wall

PROGS = change_slow change_dp change_greedy
#build all
all: change_slow change_dp change_greedy

#buld individual
change_slow:  
	${CXX} ${CXXFLAGS} change_slow.cc -o change_slow
	
change_dp: 
	${CXX} ${CXXFLAGS} change_dp.cc -o change_dp
	
change_greedy:
	${CXX} ${CXXFLAGS} change_greedy.cc -o change_greedy
	
# Typing 'make clean' calls this build.
# It's designed to clean up the folder.
# Be careful with this, edit as needed.
clean: 
	rm -f ${PROGS}  *.o *~ a.out
	
# Only needed in Windows where the .exe extension is appended
# to executables. Rather than rm -f *.exe, this leaves in
# place any other executables that might be present.
rmexes:
	rm -f change_slow.exe
	rm -f change_dp.exe
	rm -f change_greedy.exe
	

	
