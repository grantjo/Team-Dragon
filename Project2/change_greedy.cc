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
** Project 2 - Coins
** Group 34 
** Authors: Mel Drews, Jordan Grant
** File: change_greedy.cc
** Description: An implementation of the make change problem using the greedy approach.
                
**************************************************************************************/
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

#define WRITETOFILE

/*********************************************************************************************
** Function: 	makeChange
** Paramaters:	reference vector of coinValues, int amount to make change,
**			    reference vector of quantities for each coin to output
** Return: 		min number of coins used
** Description:	Greedy approach to making change given a list of coin values and an amount to make change.
**              Uses a buffer for the number of coins needed at each value leading up to the target value.
**********************************************************************************************/
int makeChange(std::vector<int>& coinValues, int change, std::vector<int>& outputCoins);

/*********************************************************************************************
** Function: 	writeToOutput
** Paramaters:	reference to ofstream, reference to vector<int>, pointer to MaximumSub return values
** Return: 		void
** Description:	Outputs the original coinsUseday, maximum subcoinsUseday, and maximum sum as follows:
**				[a1, a2, a3, ..., an]
**				[aj, aj+1, ..., ai-1, ai]
**				max
**
**				where 0 <= j <= i <= n
**********************************************************************************************/
void writeToOutput(std::ofstream& out, std::vector<int>& outputCoins, int minCoins);

/*********************************************************************************************
** Function: 	writeToConsole
** Paramaters:	reference to vector<int>, pointer to int MaximumSub return values,
** Return: 		void
** Description:	Outputs the original coinsUseday, maximum subcoinsUseday, maximum sum, and time(ns) for call to console as follows:
**				[a1, a2, a3, ..., an]
**				[aj, aj+1, ..., ai-1, ai]
**				max
** 				Time (ns): <time>
**
**				where 0 <= j <= i <= n
**********************************************************************************************/
void writeToConsole(std::vector<int>& coinsUsed, int minCoins, long nanoseconds);

/*********************************************************************************************
** Function: 	parsecoinsUseday
** Paramaters:	value of coinsUseday string, reference to empty vector<int>
** Return: 		void
** Description:	string is read into a stream, which is parsed by comma delimited getline calls.
**				Each comma delimited string is converted to an int by stringstream, then pushed
**				onto vector.
**				Loop exits when getline receives an eof signal.
**********************************************************************************************/
void parseArray(std::string str, std::vector<int>&  coinValues);

int vectorFind(std::vector<int>& vector, int val);
/**  Simple function to check is string is only whitespace **/
bool only_space(const std::string &str);

int main(int argc, char** argv)
{
#ifndef WRITETOFILE
    if (argc < 2) {
	   std::cout << "Expected inputfile name in arg1" << std::endl;
	   return 1;
    }
    std::string inputFileName = argv[1];
#else
    if (argc < 3) {
        std::cout << "Expected inputfile name in arg1 and outputfile name in arg2" << std::endl;
        return 1;
    }
    std::string inputFileName = argv[1];
    std::string outputFileName = argv[2];
#endif

    std::vector<int> coinValues;		//STL container for array

    std::ifstream inputFile;	// file IO


    std::string fileLine;		// holds string representation of array


    // open input file
    inputFile.open(inputFileName);
    if (inputFile.fail())
    {
        // Report error and return if file failed to open
        std::cout << "Could not open file" << std::endl;
        return -1;
    }
#ifndef WRITETOFILE

    while (std::getline(inputFile, fileLine)) { 				//read entire line from file into fileLine, until eof
	   if (!only_space(fileLine)) {							//check if line is whitespace
		  std::string sChange = "";
		  //int iChange;

		  std::getline(inputFile, sChange);
          std::vector<int> changeAmount;
		  parseArray(sChange, changeAmount);

		  parseArray(fileLine, coinValues);

          int size = changeAmount.size();

          for (int i = 0; i < size; i++) {
              std::vector<int> outputCoins(coinValues.size(), 0); //store the coins actually used

              //int size = outputCoins.size();

              auto begin = std::chrono::high_resolution_clock::now();
              int minCoins = makeChange(coinValues, changeAmount[i], outputCoins);
              auto endd = std::chrono::high_resolution_clock::now();
              long elapsed = (long) std::chrono::duration_cast<std::chrono::nanoseconds>(endd - begin).count();

              writeToConsole(outputCoins, minCoins, elapsed);
          }
		  std::vector<int>().swap(coinValues);			// free memory for vector, initialize new vector
	   }
    }
    inputFile.close();
#else
    std::ofstream outputFile;
    // open output file, creates file if none exists
    outputFile.open(outputFileName);

    outputFile << "Algorithm changegreedy:\n";

    while (std::getline(inputFile, fileLine)) { 				//read entire line from file into fileLine, until eof

        if (!only_space(fileLine)) {							//check if array is not whitspace
            std::string sChange = "";
            int iChange;

            std::getline(inputFile, sChange);
            std::stringstream toInt(sChange);

            toInt >> iChange;

            parseArray(fileLine, coinValues);

            std::vector<int> outputCoins(coinValues.size(), 0); //store the coins actually used

            int minCoins = makeChange(coinValues, iChange, outputCoins);

            writeToOutput(outputFile, outputCoins, minCoins);

            std::vector<int>().swap(coinValues);				// free memory for vector, initialize new vector
            minCoins = 0;
        }
    }
    inputFile.close();										    //close files
    outputFile.close();
#endif
}

/*********************************************************************************************
** Function: 	makeChange
** Paramaters:	reference vector of coinValues, int amount to make change,
**			    reference vector of quantities for each coin to output
** Return: 		min number of coins used
** Description:	Greedy approach to making change given a list of coin values and an amount to make change.
**              Uses a buffer for the number of coins needed at each value leading up to the target value.
**********************************************************************************************/
int makeChange(std::vector<int>& coinValues, int change, std::vector<int>& outputCoins)
{
    int minCoins = 0;
    int testCoin = coinValues.size()-1;
    while ((change > 0)&& (testCoin >= 0)){
        if (coinValues[testCoin] <= change){
            outputCoins[testCoin] = change/coinValues[testCoin];
            change -= (outputCoins[testCoin] * coinValues[testCoin]);
            minCoins += outputCoins[testCoin];
        }
        --testCoin;
    }

    return minCoins;
}



/*********************************************************************************************
** Function: 	writeToOutput
** Paramaters:	reference to ofstream, reference to vector<int>, int equal to minimum coins
** Return: 		void
** Description:	Outputs the original coinsUseday, maximum subcoinsUseday, and maximum sum as follows:
**				[a1, a2, a3, ..., an]
**				[aj, aj+1, ..., ai-1, ai]
**				max
**
**				where 0 <= j <= i <= n
**********************************************************************************************/
void writeToOutput(std::ofstream& out, std::vector<int>& outputCoins, int minCoins) {
    int size = outputCoins.size();
    out << "[";										//output open bracket

    for (int i = 0; i < size; i++) {					// output original coinsUsed comma delimited
        if (i + 1 == size)
            out << outputCoins[i];
        else
            out << outputCoins[i] << ", ";
    }

    out << "]\n" << minCoins << "\n\n";				// output closing bracket, number of coins, and padding newlines
}

/*********************************************************************************************
** Function: 	writeToConsole
** Paramaters:	reference to vector<int>, int equal to minimum coins
** Return: 		void
** Description:	Outputs the original coinsUseday, maximum subcoinsUseday, maximum sum, and time(ns) for call to console as follows:
**				[a1, a2, a3, ..., an]
**				[aj, aj+1, ..., ai-1, ai]
**				max
** 				Time (ns): <time>
**
**				where 0 <= j <= i <= n
**********************************************************************************************/
void writeToConsole(std::vector<int>& coinsUsed, int minCoins, long nanoseconds) {
    int size = coinsUsed.size();
    std::cout << "[";										//output open bracket

    for (int i = 0; i < size; i++) {					// output original coinsUseday comma delimited
        if (i + 1 == size)
            std::cout << coinsUsed[i];
        else
            std::cout << coinsUsed[i] << ", ";
    }


    // output closing bracket, sum, time, and padding newlines
    std::cout << "]\n" << minCoins << "\nTime(ns): " << nanoseconds << "\n\n";
}

/*********************************************************************************************
** Function: 	parseArray
** Paramaters:	value of coinsUseday string, reference to empty vector<int>
** Return: 		void
** Description:	string is read into a stream, which is parsed by comma delimited getline calls.
**				Each comma delimited string is converted to an int by stringstream, then pushed
**				onto vector.
**				Loop exits when getline receives an eof signal.
**********************************************************************************************/
void parseArray(std::string str, std::vector<int>& coinValues) {
    // remove opening and closing bracket
    str.erase(0, 1);
    str.erase(str.size() - 1);

    // initialize stringstreams for whole string and each integer
    std::stringstream ss(str),
            ss_temp;

    // temperary storage for each value in coinsUseday
    std::string s_temp;
    int i_temp;

    while (std::getline(ss, s_temp, ',')) {			// get each comma delimited value
        ss_temp << s_temp;							// read into string
        ss_temp >> i_temp;							// write out to int

        coinValues.push_back(i_temp);				// push onto vector

        // reset ss_temp for next value
        ss_temp.str("");
        ss_temp.clear();
    }

}

/** Simple find function for vectors, returns index if found and -1 if not  **/
int vectorFind(std::vector<int>& vector, int val)
{
    int size = vector.size();

    for (int i = 0; i < size; i++) {
        if (vector[i] == val)
            return i;
    }
    return -1;
}

/**  Simple function to check is string is only whitespace **/
bool only_space(const std::string &str)
{
    for (std::string::const_iterator it = str.begin(); it != str.end(); it++)
    {
        if (*it == '\t')
            continue;
        else if (*it != ' ')
            return false;
    }
    return true;
}
