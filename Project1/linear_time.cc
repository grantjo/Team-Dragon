/**********************************************************************************************
** Project 1 - Algorithm 2, Linear Time implementation
** Project Group: Team Dragon
** Authors: Mel Drews,  Jordan Grant
** Description: Improves on brute-force Enumeration by eliminating some redundant calculations
**				Algorithm Pseudocode:
**
**				MaximumSub(array)
**					max = array[0], start = 0, end = 0
**					for i = 0 to n
**						temp = 0
**						for j = i to 0
**							temp += array[j]
**							if temp > max
**								max = temp
**								start = j
**								end = i
**						endfor
**					endfor
**					return max, start, end
**
**				Overview of Test program
** 				1) An array of the form "[a1, a2, a3,..., an]" is read from a file
** 				2) The information is parsed into a STL vector using the stringstream class
** 				3) The vector is passed to MaximumSub which returns the sum, start index, and stop
**					index of the maximum subarray in an integer array
**				4) The original array, subarray, and maximum sum are written to an output file in
**					the following form:
**					[a1, a2, a3, ..., an]
**					[aj, aj+1, ..., ai-1, ai]
**					max
**				5) The process is completed for all arrays in test file
***********************************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>

/*********************************************************************************************
** Function: 	MaximumSub
** Paramaters:	reference to vector<int>
** Return: 		Array of 3 integers a[0] = max sum, a[1] = sub start index, a[2] = sub end index
** Description:	Brute Force Maximum Subarray algorithm. Iterates over array and, for every index,
**					calculates sum from index to 0.
**				If a new maximum sum is found, it is saved, along with the start/stop indices in
**					larger array
**				The final max sum, start/stop indices are returned in an array.
**********************************************************************************************/
int* MaximumSub(std::vector<int>& arr);

/*********************************************************************************************
** Function: 	writeToOutput
** Paramaters:	reference to ofstream, reference to vector<int>, pointer to MaximumSub return values
** Return: 		void
** Description:	Outputs the original array, maximum subarray, and maximum sum as follows:
**				[a1, a2, a3, ..., an]
**				[aj, aj+1, ..., ai-1, ai]
**				max
**
**				where 0 <= j <= i <= n
**********************************************************************************************/
void writeToOutput(std::ofstream& out, std::vector<int>& arr, int maxSub[]);

/*********************************************************************************************
** Function: 	parseArray
** Paramaters:	value of array string, reference to empty vector<int>
** Return: 		void
** Description:	string is read into a stream, which is parsed by comma delimited getline calls.
**				Each comma delimited string is converted to an int by stringstream, then pushed
**				onto vector.
**				Loop exits when getline receives an eof signal.
**********************************************************************************************/
void parseArray(std::string str, std::vector<int>&  arr);


/// Main Function
int main(int argc, char** argv)
{
    int *maxSub;				// to hold values for maximum subarray
    std::vector<int> array;		//STL container for array

    std::ifstream inputFile;	// file IO
    std::ofstream outputFile;

    std::string fileLine;		// holds string representation of array


    // open input file
    inputFile.open("MSS_TestProblems.txt" );
    if (inputFile.fail())
    {
        // Report error and return if file failed to open
        std::cout << "Could not open file" << std::endl;
        return -1;
    }

    // open output file, creates file if none exists
    outputFile.open("MSS_TestResults.txt");

    // set t1 = time before testing arrays
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    while(std::getline(inputFile, fileLine)) { 				//read entire line from file into fileLine, until eof

        if (fileLine.size() > 2) {							//check if array is not empty ([])
            parseArray(fileLine, array);

            maxSub = MaximumSub(array);

            writeToOutput(outputFile, array, maxSub);

            delete[] maxSub;								// free memory for maximum subarray
            std::vector<int>().swap(array);					// free memory for vector, initialize new vector
        }
    }

    // t2 = time after testing arrays
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<long double> time_span =
            std::chrono::duration_cast<std::chrono::duration<long double>>(t2 - t1);

    std::cout << "All arrays tested in : " << time_span.count()
              << " seconds." << std::endl;

    inputFile.close();										//close files
    outputFile.close();
}

/*********************************************************************************************
** Function: 	MaximumSub
** Paramaters:	reference to vector<int>
** Return: 		Array of 3 integers a[0] = max sum, a[1] = sub start index, a[2] = sub end index
** Description:	Brute Force Maximum Subarray algorithm. Iterates over array and, for every index,
**					calculates sum from index to 0.
**				If a new maximum sum is found, it is saved, along with the start/stop indices in
**					larger array
**				The final max sum, start/stop indices are returned in an array.
**********************************************************************************************/
int* MaximumSub(std::vector<int>& arr) {
    int *maxSub = new int[3],			// create 3 integer array
            size = arr.size();
    maxSub[0] = 0;					// initial values for maxSub
    maxSub[1] = 0;
    maxSub[2] = 0;
    int midSum = 0;                    // tracks sum from the previous loop
    int currSum = 0;
    int oldMax = 0;

    for (int i = 0; i < size; i++) {
        oldMax = maxSub[0];
        int tempSum = 0;
        currSum = midSum + arr[i];
        if (currSum > 0) {
            maxSub[0] = maxSub[0] + currSum;
            maxSub[2] = i;

            if (abs(midSum) < oldMax){      // Do we need a new beginning for maxSub?
                int oldStart = maxSub[1];
                for (int j = i; j >= oldStart; j--) {  // there will be a new maxSub
                    tempSum += arr[j];
                    if (tempSum > maxSub[0]) {    // maxSub found, update information
                        maxSub[0] = tempSum;
                        maxSub[1] = j;
                    }
                }
            } else if (arr[i] > oldMax) {
                maxSub[0] = arr[i];
                maxSub[1] = i;
                maxSub[2] = i;
                midSum = 0;
            }

            midSum = 0;     // there are no more intervening indices

        } else if (arr[i] > oldMax) {
            maxSub[0] = arr[i];
            maxSub[1] = i;
            maxSub[2] = i;
            midSum = 0;
        }
        else {
            midSum = currSum;
        }
    }
    return maxSub;
}

/*********************************************************************************************
** Function: 	writeToOutput
** Paramaters:	reference to ofstream, reference to vector<int>, pointer to MaximumSub return values
** Return: 		void
** Description:	Outputs the original array, maximum subarray, and maximum sum as follows:
**				[a1, a2, a3, ..., an]
**				[aj, aj+1, ..., ai-1, ai]
**				max
**
**				where 0 <= j <= i <= n
**********************************************************************************************/
void writeToOutput(std::ofstream& out, std::vector<int>& arr, int maxSub[]) {
    int size = arr.size();

    out << "[";										//output open bracket

    for(int i = 0; i < size; i++) {					// output original array comma delimited
        if (i + 1 == size)
            out << arr[i];
        else
            out << arr[i] << ", ";
    }

    out << "]\n[";									// output closing bracket and opening for subarray

    for (int i = maxSub[1]; i <= maxSub[2]; i++) {	// output comma delimited subarray
        if (i == maxSub[2])
            out << arr[i];
        else
            out << arr[i] << ", ";
    }

    out << "]\n" << maxSub[0] << "\n\n";				// output closing bracket, sum, and padding newlines
}

/*********************************************************************************************
** Function: 	parseArray
** Paramaters:	value of array string, reference to empty vector<int>
** Return: 		void
** Description:	string is read into a stream, which is parsed by comma delimited getline calls.
**				Each comma delimited string is converted to an int by stringstream, then pushed
**				onto vector.
**				Loop exits when getline receives an eof signal.
**********************************************************************************************/
void parseArray(std::string str, std::vector<int>& arr) {
    // remove opening and closing bracket
    str.erase(0, 1);
    str.erase(str.size() - 1);

    // initialize stringstreams for whole string and each integer
    std::stringstream ss(str),
            ss_temp;

    // temperary storage for each value in array
    std::string s_temp;
    int i_temp;

    while(std::getline(ss, s_temp, ',')) {			// get each comma delimited value
        ss_temp << s_temp;							// read into string
        ss_temp >> i_temp;							// write out to int

        arr.push_back(i_temp);						// push onto vector

        // reset ss_temp for next value
        ss_temp.str("");
        ss_temp.clear();
    }

}

