#pragma once

#include <vector>
#include "city.h"
using namespace std;


class tsp
{
public:
	tsp(int);
	~tsp();

	vector<city>cities;
	vector<city>tour;
	vector<city>newTour;

	int getDistance(city a, city b);
	int getTotalDistance(vector<city>);
	int nearest(int c, bool *, int size);
	void nearestNeighbor();
	void TwoOpt();
	void TwoOptSwap(int i, int k);

	int **distMatrix;
	

private:
	
};

