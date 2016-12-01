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
#include <cstring>
#include <string>
#include <limits>
#include <cmath>

#endif //MY_INCLUDES

#ifndef PROJECT4_GRAPH_H
#define PROJECT4_GRAPH_H


class Graph {
public:
    Graph(std::string);


protected:
    struct vertex {
        int num;
        int xcoor;
        int ycoor;
    };

    void parseArray(std::ifstream&, const std::string, std::vector<vertex>&);
    void distMatrix(std::vector<std::vector<int>>&, std::vector<vertex>&);

private:
    std::vector<std::vector<int>> Distances;        //2D vector
    std::string fileLine;
    const int inf = std::numeric_limits<int>::max();
};

#endif //PROJECT4_GRAPH_H
