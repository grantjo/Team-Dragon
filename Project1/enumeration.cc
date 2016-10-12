/**********************************************************************************************
** Project 1 - Algorithm 1, Enumeration implementation
** Project Group: Team Dragon
** Authors: Mel Drews,  Jordan Grant
** Description:
***********************************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

/// Function Prototypes
int* MaximumSub(std::vector<int> arr);
void writeToOutput(std::ofstream& out, std::vector<int>& arr, int maxSub[]);
void parseArray(std::string str, std::vector<int>&  arr);


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
			fileLine.erase(0,1);
      fileLine.erase(fileLine.size() - 1);
      
      parseArray(fileLine, array);
			
      maxSub = MaximumSub(array);
		  
      writeToOutput(outputFile, array, maxSub); 
      
      delete[] maxSub;
      std::vector<int>().swap(array);
    }
	}
  inputFile.close();
  outputFile.close();
}

/// Function Implementations
int* MaximumSub(std::vector<int> arr) {
	int *maxSub = new int[3],
      size = arr.size();
  maxSub[0] = arr[0];
  maxSub[1] = 0;
  maxSub[2] = 0;

  for (int i = 0; i < size; i++) {
    int tempSum = 0;
    for (int j = i; j >= 0; j--) {
      tempSum += arr[j];
      if (tempSum > maxSub[0]) {
        maxSub[0] = tempSum;
        maxSub[1] = j;
        maxSub[2] = i;
      }
    }
  }
  return maxSub;
}

void writeToOutput(std::ofstream& out, std::vector<int>& arr, int maxSub[]) {
  int size = arr.size();
  out << "[";
  for(int i = 0; i < size; i++) {
    if (i + 1 == size)
      out << arr[i];
    else
      out << arr[i] << ',';
  }
  out << "]\n[";
  for (int i = maxSub[1]; i <= maxSub[2]; i++){
    if (i == maxSub[2])
      out << arr[i];
    else
      out << arr[i] << ',';
  }
  out << "]\n" << maxSub[0] << "\n\n";
}

void parseArray(std::string str, std::vector<int>& arr) {
	std::stringstream ss(str),
					  ss_temp;
	std::string s_temp;
	int i_temp;
	while(std::getline(ss, s_temp, ',')) {
		ss_temp << s_temp;
		ss_temp >> i_temp;
		
    arr.push_back(i_temp);
		
    ss_temp.str("");
		ss_temp.clear();
	}
	
}

