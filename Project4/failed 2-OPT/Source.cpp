#include <iostream>
#include <fstream>
#include <vector>
#include "tsp.h"
using namespace std;

#define DEBUG 1

int main(int argc, char** argv) 
{
	string inFile, outFile;
	inFile = outFile = argv[1];

	ifstream read(inFile);

	//inStr.open(inFile, ios::in);

	tsp tsp(0);

	if (!read)
	{
		cerr << "Cant open file" << endl;
		return 0;
	}

	int c, x, y;
	while (read >> c >> x >> y)
	{
		//inStr >> c >> x >> y;

		city *newCity = new city(c, x, y);

		tsp.cities.push_back(*newCity);
	}

	read.close();

	if (0)
	{
		for (size_t i = 0; i < tsp.cities.size(); i++)
		{
			cout << tsp.cities[i].getCity() << endl;
		}

		cout << "Num cities:" << tsp.cities.size() << endl;

		cout << endl;
	}

	tsp.nearestNeighbor();

	if (DEBUG)
	{
		cout << tsp.getTotalDistance(tsp.tour) << endl;
	}

	tsp.TwoOpt();

	string ofile = outFile + ".tour";

	std::ofstream ofs;
	ofs.open(ofile, std::ofstream::out | std::ofstream::app);

	ofs << tsp.getTotalDistance(tsp.tour) << endl;

	for (int i = 0; i < tsp.tour.size(); ++i)
	{
		ofs << tsp.tour[i].getCity() << endl;
	}

	ofs.close();

	if (DEBUG)
	{
		cout << tsp.getTotalDistance(tsp.tour) << endl;
	}
}
