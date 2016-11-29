/**************************************************************************************
** Project 4 - Graph class implementation headers
        ** Group 34
** Authors: Mel Drews, Jordan Grant, Adrian Buenavista
        ** File: graph.h
        ** Description: Headers for associated Graph class

**************************************************************************************/

#ifndef MY_INCLUDES
#define MY_INCLUDES
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <sys/fcntl.h>

#endif //MY_INCLUDES

#ifndef PROJECT4_GRAPH_H
#define PROJECT4_GRAPH_H

struct vertex {
    int num, xcoor, ycoor;
};

typedef std::vector<vertex> Row;
typedef std::vector<Row> Matrix;

class Graph {
public:
    Graph(std::string);

private:
    Row row1;
    Row* row1_ptr = &row1;
    Matrix myMatrix;
    std::string fileLine;
};

/*********************************************************************************************
** Function: 	parseArray
** Paramaters:
** Return: 		void
        ** Description:	string is read into a stream, which is parsed by comma delimited getline calls.
**				Each comma delimited string is converted to an int by stringstream, then pushed
**				onto vector.
**				Loop exits when getline receives an eof signal.
**********************************************************************************************/
//void parseArray(std::string str, Row&);


#endif //PROJECT4_GRAPH_H
