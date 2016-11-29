#########################################################
# File: Makefile
# Description: A more robust makefile for CS162.
# You need to edit the variables under "USER SECTION"
#########################################################

# #'s are line-comments 

# CXX is a standard variable name used for the compiler. 
CXX = g++

# CXXFLAGS is a standard variable name for compile flags.
# -std=c++0x specifies to use a certain language version.
CXXFLAGS = -std=c++11

# -Wall turns on all warnings
CXXFLAGS += -Wall

# -pedantic-errors strictly enforces the standard
CXXFLAGS += -pedantic-errors

# -g turns on debug information 
DBGFLAG += -g

####################
### USER SECTION ###
####################

# SRCS is a standard name for the source files. 
# Edit as needed.
SRC1 = main.cpp
SRC2 = graph.cpp
SRCS = ${SRC1} ${SRC2}

# HEADERS is a standard name for the header files.
# Edit these as needed.
HEADER1 = graph.h
HEADERS = ${HEADER1}

# These will be your executable names. 
# Edit as needed.
PROG1 = tsp
#PROG2 = lab1-2
#PROGS = ${PROG1} ${PROG2}
PROGS = ${PROG1}

#####################
### BUILD SECTION ###
#####################

# Typing 'make' in terminal calls the first build availible.
# In this case, all.
all:
	${CXX} ${CXXFLAGS} ${SRCS} -o ${PROG1}
	
	
debug:
	${CXX} ${CXXFLAGS} ${DBGFLAG} ${SRCS} -o ${PROG1}


# Typing 'make clean' calls this build.
# It's designed to clean up the folder.
# Be careful with this, edit as needed.
clean: 
	rm -f ${PROGS} *.o *~

