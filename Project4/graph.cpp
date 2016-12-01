/*************************************************************************************
**************************************************************************************
*****                          ______________                                    *****
*****                    ,===:'.,            `-._                                *****
*****                           `:.`---.__         `-._                          *****
*****                             `:.     `--.         `.                        *****
*****                               \.        `.         `.                      *****
*****                       (,,(,    \.         `.   ____,-`.,                   *****
*****                    (,'     `/   \.   ,--.___`.'                            *****
*****                ,  ,'  ,--.  `,   \.;'         `                            *****
*****                 `{D, {    \  :    \;                                       *****
*****                   V,,'    /  /    //                                       *****
*****                   j;;    /  ,' ,-//.    ,---.      ,                       *****
*****                   \;'   /  ,' /  _  \  /  _  \   ,'/                       *****
*****                         \   `'  / \  `'  / \  `.' /                        *****
*****                          `.___,'   `.__,'   `.__,'  John VanderZwag        *****
**************************************************************************************
* 888888 888888    db    8b    d8     8888b.  88""Yb    db     dP""b8  dP"Yb  88b 88 *
*   88   88__     dPYb   88b  d88      8I  Yb 88__dP   dPYb   dP   `" dP   Yb 88Yb88 *
*   88   88""    dP__Yb  88YbdP88      8I  dY 88"Yb   dP__Yb  Yb  "88 Yb   dP 88 Y88 *
*   88   888888 dP""""Yb 88 YY 88     8888Y"  88  Yb dP""""Yb  YboodP  YbodP  88  Y8 *
**************************************************************************************
** Project 4 - Graph class implementation
** Group 34
** Authors: Mel Drews, Jordan Grant, Adrian Buenavista
** File: graph.cpp
** Description: Methods and members for a Graph class

**************************************************************************************/

#include "graph.h"

Graph::Graph(std::string inFile) {             //Constructor
    std::ifstream inputFile;
    std::vector<vertex> Vertices;                   //vector of vertices

    inputFile.open(inFile);

    if(!inputFile.is_open()) {
        // Report error and return if file failed to open
        std::cout << "Could not open file" << std::endl;
        exit(EXIT_FAILURE);
    }

    parseArray(inputFile, inFile, Vertices);

    unsigned long cols, rows;
    cols = Vertices.size();
    rows = Vertices.size();
    Distances.resize(rows, std::vector<int>(cols));

    //initialize all distances to infinity
    for(unsigned long row = 0; row < rows; row++){
        for(unsigned long col = 0; col < cols; col++) {
            Distances[row][col] = inf;
        }
    }

    distMatrix(Distances, Vertices);                      //Calculate correct distances
}


/*********************************************************************************************
** Function: 	parseArray
** Paramaters:  a string representing the filename for input
** Return: 		void
** Description:	string is read into a stream, which is parsed by comma delimited getline calls.
**				Each comma delimited string is converted to an int by stringstream, then pushed
**				onto vector.
**				Loop exits when getline receives an eof signal.
**********************************************************************************************/
void Graph::parseArray(std::ifstream &inputFile, const std::string inFile, std::vector<vertex> &Vertices) {
    /*inputFile.open(inFile);

    if(!inputFile.is_open()) {
        // Report error and return if file failed to open
        std::cout << "Could not open file" << std::endl;
        exit(EXIT_FAILURE);
    }*/

    std::string fileLine;		                    // holds string representation of array
    const char delimiter[] = " ";

    while (std::getline(inputFile, fileLine)) {     //read entire line from file into fileLine, until eof
        int nodeNum, nodeX, nodeY;
        char * cstr = new char [fileLine.length()+1];
        std::strcpy(cstr, fileLine.c_str());
        char * myToken;

        myToken = strtok(cstr, delimiter);
        nodeNum = atoi(myToken);

        myToken = strtok(NULL, delimiter);
        nodeX = atoi(myToken);

        myToken = strtok(NULL, delimiter);
        nodeY = atoi(myToken);

        Vertices.push_back({nodeNum, nodeX, nodeY});

        delete myToken;
    }
}

void Graph::distMatrix(std::vector<std::vector<int>> &Distances, std::vector<vertex> &Vertices) {
    int distance = 0;
    double calcDist;

    for (unsigned long row = 0; row < Vertices.size(); row++) {
        for (unsigned long col = 0; col <= row; col++) {
            if (col == row) {
                Distances[row][col] = 0;
                break;
            }

            calcDist = floor(sqrt(pow((Vertices[row].xcoor - Vertices[col].xcoor), 2.0)
                                   + pow((Vertices[row].ycoor - Vertices[col].ycoor), 2.0)) + 0.5);
            distance = static_cast<int>(calcDist);
            Distances[row][col] = distance;
        }
    }
}