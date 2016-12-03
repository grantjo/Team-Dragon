#include <climits>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cmath>
#include "tsp.h"


tsp::tsp(int dist)
{
}


tsp::~tsp()
{
}

int tsp::getDistance(city a, city b)
{
	int dx = pow((float)(a.getX() - b.getX()), 2);
	int dy = pow((float)(a.getY() - b.getY()), 2);
	return (floor((float)(sqrt(dx + dy)) + 0.5)); //Rounds down from 0.0 to .499_, rounds up from 0.5 to .99_
}


int tsp::nearest(int cityID, bool * visited, int size)
{
	int nearestDist = INT_MAX;
	int nearestCity = INT_MAX;

	for (size_t i = 0; i < size; i++)
	{
		if (visited[i] == true)
		{
			continue;
		}

		//skip if it is its own city, otherwise it will always be always the closest to itself....
		if (i == cityID)
		{
			continue;
		}

		int temp = getDistance(cities[cityID], cities[i]);

		if (temp < nearestDist)
		{
			nearestDist = temp;
			nearestCity = i;
		}
	}

	return nearestCity;
}

void tsp::nearestNeighbor()
{
	int numCities = cities.size();

	bool * visited;
	visited = new bool[numCities];
	int count = 0;
	int startCity;
	int last;

	for (size_t i = 0; i < numCities; i++)
	{
		visited[i] = false;
	}



	srand(time(NULL));
	startCity = rand() % (cities.size() - 0) + 0;

	last = startCity;  //make this start city a random number, but this should do for now....
	while (count < numCities - 1)
	{

		int next = nearest(last, visited, numCities);

		tour.push_back(cities[last]);
		visited[last] = true;

		last = next;

		count++;
	}

	tour.push_back(cities[startCity]);

}

int tsp::getTotalDistance(vector<city> v)
{
	int totalDistance = 0;

	for (size_t i = 0; i < v.size() - 1;)
		for (size_t j = i + 1; j < v.size();)
		{
			totalDistance += getDistance(v[i], v[j]);
			i++;
			j++;
		}

	totalDistance += getDistance(cities[v.size() - 1], v[0]);

	return totalDistance;
}

void tsp::TwoOpt()
{
	int size = cities.size();

	int bestDistance = getTotalDistance(tour);

	//copy tour vector
	newTour = tour;

	int count = 0;
	while (count < 50)
	{

		for (int i = 0; i < size - 1; i++)
		{
			for (int k = i + 1; k < size; k++)
			{
				TwoOptSwap(i, k);

				int newDistance = getTotalDistance(newTour);

				//cout << "new dist: " << newDistance << endl;

				if (newDistance < bestDistance)
				{
					tour = newTour;
					bestDistance = newDistance;
				}
			}
		}


		count++;
	}
	//copy tour vector
	//newTour = tour;

	//for (int i = 0; i < size - 1; i++)
	//{
	//	for (int k = i + 1; k < size; k++)
	//	{
	//		TwoOptSwap(i, k);

	//		int newDistance = getTotalDistance(newTour);

	//		if (newDistance < bestDistance)
	//		{
	//			tour = newTour;
	//			bestDistance = newDistance;
	//		}
	//	}
	//}

}

void tsp::TwoOptSwap(int i, int k)
{
	int size = cities.size();

	// 1. take route[0] to route[i-1] and add them in order to new_route
	for (int c = 0; c <= i - 1; ++c)
	{
		newTour[c] = tour[c];
	}

	// 2. take route[i] to route[k] and add them in reverse order to new_route
	for (int c = k; c >= i; c--)
	{
		int j = i;
		newTour[j] = tour[c];
		j++;
	}

	// 3. take route[k+1] to end and add them in order to new_route
	for (int c = k + 1; c < size; ++c)
	{
		newTour[c] = tour[c];
	}

}