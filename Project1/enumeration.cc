/**************************************************************************************************************
** Project 1 - Algorithm 1, Enumeration implementation
** Project Group: Team Dragon
** Authors: Mel Drews,  Jordan Grant
** Description:
***************************************************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define CAPACITY 20

/// Function Prototypes
int* MaximumSub(int arr[], int size);
void writeToOutput(std::ofstream out, int arr[], int maxSub[]);
int* parseArray(std::string str);
int* resizeArray(int arr[],  int capacity) ;

/// Main Function
int main(int argc, char** argv)
{
	int *arr,
		 *maxSub;
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
			
			arr = parseArray(fileLine);
			//maxSub = MaximumSub(arr);
		
		}
	}

}

/// Function Implementations
int* MaximumSub(int arr[]) {
	int maxSub = new int[3];
}

void writeToOutput(std::ofstream out, int arr[], int maxSub[]) {
	out << "[";
	for (int i = 1; i < arr[0]; i++)
		out << arr[i] << ","
}

int* parseArray(std::string str) {
	std::stringstream ss(str);
	 int *array = new int[CAPACITY],
			capacity = CAPACITY;
			
	for(array[0] = 1; std::getline(ss, array[i], ","); array[0]++) {
		if (array[0]  >= capacity) {
			capacity *= 2;
			array = resizeArray(array, capacity);
		}
	}
	
	
	return array;
}

int* resizeArray(int arr[], int capacity) {
	int* newArray = new int[capacity];
	
	for (int i = 0; i < arr[0]; i++) {
		newArray[i] = arr[i];
	}
	
	delete[] arr;
	return newArray
}