#pragma once

#include <vector>
using namespace std;

class city
{
	

public:

city()
{
}

city(int id, int xcoord, int ycoord)
{
	c = id;
	x = xcoord;
	y = ycoord;
	visited = false;
}


~city()
{
}

	bool visited;

	int getCity()
	{
		return c;
	}

	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}



private:
	int c;
	int x;
	int y;
};

