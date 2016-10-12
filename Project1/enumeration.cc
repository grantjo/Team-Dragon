/**************************************************************************************************************
** Project 1 - Algorithm 1, Enumeration implementation
** Project Group: Team Dragon
** Authors: Mel Drews,  Jordan Grant
** Description:
***************************************************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#define CAPACITY 20

/// Function Prototypes
int* MaximumSub(std::vector<int> arr);
void writeToOutput(std::ofstream out, std::vector<int> arr, int maxSub[]);
void parseArray(std::string str, std::vector<int>  arr);


/// Main Function
int main(int argc, char** argv)
{
	int *maxSub;
	std::vector<int> array;
	std::ifstream inputFile;
	std::ofstream outputFile;
	std::string fileLine;
	
	inputFile.open("MSS_TestProblems.txt" );
	if (inputFile.fail())
    {
        std::cout << "Could not open file" << std::endl; 
        return -1;
    }
	
	outputFile.open("MSS_TestResults.txt");
	
	while(std::getline(inputFile, fileLine)){
		if (fileLine.size() > 2) {
			fileLine.erase(0, 1);
			fileLine.erase(fileLine.size() - 1);
			parseArray(fileLine, array);
			//maxSub = MaximumSub(array);
			for (int i = 0; i < array.size(); i++)
				std::cout << array[i] << std::endl;
			std::cout << std::endl;
		}
	}

}

/// Function Implementations
int* MaximumSub(std::vector<int> arr) {
	int maxSub = new int[3];
}

void writeToOutput(std::ofstream out, std::vector<int> arr, int maxSub[]) {
	out << "[";
	for (int i = 1; i < arr[0]; i++)
		out << arr[i] << ","
}

void parseArray(std::string str, std::vector<int> arr) {
	std::stringstream ss(str),
					  ss_temp;
	std::string s_temp;
	int i_temp
	for(int i = 0; std::getline(ss, s_temp, ","); i++) {
		ss_temp << s_temp;
		ss_temp >> i_temp;
		arr.push_back(i_temp);
		
		ss_temp.str("");
		ss_temp.clear();
	}
	
}

