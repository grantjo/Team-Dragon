#include<chrono>
#include<fstream>
#include<iostream>
#include<cstdlib>
#include<sstream>
#include <vector>
#include <cmath>

#define WRITETOFILE

using namespace std;
/*
*Function: existence
*Paramaters: list of coins (int array), and int value that you want to find.
*Return: int which indecate the location of the value.
*Description: This function will find if there is a value in the array.
			If there is value, it returns the location of the value.
			If not, it will retrun -1.
*/
int existence(int* V,int A, int sizeOfList);

/*
*Function: coin_counter
*Paramaters: array that indecates the number of each coins.
*Return: int which indecate the number of coins.
*Description: This function will count the number of coins.
*/
int coin_counter(int* coin_array, int sizeOfList);

/*
*Function: only_space
*Paramaters: string
*Return: bool
*Description: check if it's string with space.
*/
bool only_space(const string &str);

/*
*Function: parseArray
*Paramaters: string(string that needs to be changed to int array) and vector(coin values).
*Return: none
*Description: convert string each value in str to integer and put it in vector.
*/
void parseArray(string str, vector<int>& coinValues);

/*
*Function: changeslow
*Paramaters: list of coins (int array), and int value that you want for change, coin_count, and min_coin for the minimum combination
*Return: none
*Description: This function will find the smallest combination of coins.
*the algorithm is like this:
*if the coin exist that match the change
	return the array that counts only that coin.
	ex) [1,2,3] change:3, return [0,0,1]
else
	for i size of list of coin array{
		C1[] = changeslow(V[],V[i])
		C2[] = changeslow(V[],A-V[i]) //A is the change
		if i is 0
			list of the number of coin = combined C1[] and C2[]
		else
			if list of the number of coin > combined C1[] and C2[]
				list of the number of coin = combined C1[] and C2[]
	}return list of the number of coin;
*/
void changeslow(int* V,int A, int sizeOfList, int* coin_count, int* min_coin);

int main(int argc, char** argv){
	#ifndef WRITETOFILE
		if(argc < 2){
			cout << "Expected inputfile name in arg1" <<endl;
			return 1;
		}
		string inputFileName = argv[1];
	#else
		if(argc < 3){
			cout<<"Expected inputfile name in arg1 and outputfile name in arg2"<<endl;
			return 1;
		}
		string inputFileName = argv[1];
		string outputFileName = argv[2];
	#endif
	
	vector<int> coinValues;
	ifstream inputFile;
	string fileLine;
	
	inputFile.open(inputFileName.c_str());
	if(inputFile.fail()){
		cout << "Could not open file"<<endl;
		return -1;
	}
	
	#ifndef WRITETOFILE
	
	while(getline(inputFile, fileLine)){
		if(!only_space(fileLine)){
			string sChange = "";
			int iChange;
			getline(inputFile, sChange);
			stringstream toInt(sChange);
			
			toInt >> iChange;
			parseArray(fileLine, coinValues);
			int sizeOfList = coinValues.size();
			int* list = new int[sizeOfList];
			//copy each element in vector to string
			for(int i = 0; i<sizeOfList; i++){
				list[i] = coinValues[i];
			}
			coinValues.clear();
			
			int coin_count[sizeOfList]; //coin_count counts the coins for each step
			for(int i = 0; i<sizeOfList; i++){
				coin_count[i]=0;
			}
			int min_coin[sizeOfList]; //min_coin is the minimum combination of the coins
			for(int i = 0; i<sizeOfList; i++){
				min_coin[i]=0;
			}
			
			//start the algorithm and measure the time
			auto begin = chrono::high_resolution_clock::now();
			changeslow(list,iChange,sizeOfList,coin_count,min_coin);
			auto endd = chrono::high_resolution_clock::now();
			long elapsed = (long) chrono::duration_cast<chrono::nanoseconds>(endd - begin).count();
			
			cout <<"coins"<<"|"<<"number of coins"<<endl;
			for(int i = 0; i<sizeOfList; i++){
				cout <<list[i]<<"       "<<min_coin[i]<<endl;
			}
			int num = coin_counter(min_coin,sizeOfList);
			cout << "The number of coins we used: "<<num<<endl;
			cout << "Time it took: "<<elapsed<<"nanoseconds"<<endl;
			delete[] list;
		}
	}
	#else
		ofstream outputFile;
		outputFile.open(outputFileName.c_str());

                outputFile << "Algorithm changeslow:\n";
		
		while(getline(inputFile, fileLine)){
			if(!only_space(fileLine)){
				string sChange = "";
				int iChange;
				getline(inputFile, sChange);
				stringstream toInt(sChange);
				
				toInt >> iChange;
				parseArray(fileLine, coinValues);
				int sizeOfList = coinValues.size();
				int* list = new int[sizeOfList];
				//copy each element in vector to string
				for(int i = 0; i<sizeOfList; i++){
					list[i] = coinValues[i];
				}
				coinValues.clear();
				
				int coin_count[sizeOfList]; //coin_count counts the coins for each step
				for(int i = 0; i<sizeOfList; i++){
					coin_count[i]=0;
				}
				int min_coin[sizeOfList]; //min_coin is the minimum combination of the coins
				for(int i = 0; i<sizeOfList; i++){
					min_coin[i]=0;
				}

				//start the algorithm and measure the time
				auto begin = chrono::high_resolution_clock::now();
				changeslow(list,iChange,sizeOfList,coin_count,min_coin);
				auto endd = chrono::high_resolution_clock::now();
				long elapsed = (long) chrono::duration_cast<chrono::nanoseconds>(endd - begin).count();
				
				//store result in file
				int num = coin_counter(min_coin,sizeOfList);
				outputFile << "[";
				for(int i =0; i<sizeOfList; i++){
					if(i+1==sizeOfList)
						outputFile << min_coin[i];
					else
						outputFile << min_coin[i] << ", ";
				}
				outputFile << "]\n" << num <<"\nTime(ns): "<< elapsed << "\n\n";
				delete[] list;
			}
		}
		inputFile.close();
		outputFile.close();
	
	#endif
}
int existence(int* V,int A, int sizeOfList){
	for(int i = 0; i<sizeOfList; i++){
		if(V[i]==A){
			return i;
		}
	}
	return -1;
}

int coin_counter(int* coin_array, int sizeOfList){
	int number_of_coins = 0;
	for(int i = 0; i<sizeOfList; i++){
		number_of_coins += coin_array[i];
	}
	return number_of_coins;
}

bool only_space(const string &str)
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

void parseArray(string str, vector<int>& coinValues) {
    // remove opening and closing bracket
    str.erase(0, 1);
    str.erase(str.size() - 1);
 
    // initialize stringstreams for whole string and each integer
    stringstream ss(str),
            ss_temp;
    // temperary storage for each value in coinsUseday
    string s_temp;
    int i_temp;
    while (getline(ss, s_temp, ',')) {			// get each comma delimited value
        ss_temp << s_temp;							// read into string
        ss_temp >> i_temp;							// write out to int
 
        coinValues.push_back(i_temp);				// push onto vector
        // reset ss_temp for next value
        ss_temp.str("");
        ss_temp.clear();
    }
 }
 
void changeslow(int* V,int A, int sizeOfList, int* coin_count, int* min_coin){
	//check the existence of coin that match the change
	//or check if the change is 0
	if(existence(V,A,sizeOfList)>=0||A==0){
		//initialize
		for(int i = 0; i<sizeOfList; i++){
			coin_count[i]=0;
			min_coin[i]=0;
		}
		if(A!=0){ //count the matching change
			coin_count[existence(V,A,sizeOfList)]=1;
			min_coin[existence(V,A,sizeOfList)]=1;
		}
	}else{
		int icoin_num[sizeOfList]; //number of coin for i
		int candidate[sizeOfList]; //candidate for minimum combination
		int level_min_coin[sizeOfList]; //min coin for each depth of algorithm
		//initialize level_min_coin
		for(int j = 0; j<sizeOfList; j++){
			level_min_coin[j] = 0;
		}
		for(int i = 0; i<sizeOfList; i++){
			if(V[i]>A){ //if the coin is bigger than the change skip it.
				
			}else{
				//add the ith coin 
				changeslow(V,V[i],sizeOfList,coin_count,min_coin);
				for(int j = 0; j<sizeOfList; j++){
					icoin_num[j]=coin_count[j];
				}
				//initialize min_coin for finding rest of the combination
				for(int j = 0; j<sizeOfList; j++){
					min_coin[j] = 0;
				}
				//find rest of the combination
				changeslow(V,A-V[i],sizeOfList,coin_count,min_coin);
				for(int j = 0; j<sizeOfList; j++){
						if(coin_counter(min_coin,sizeOfList) > 1){//if min_coin is large than 1 copy min_coin to coin_count
																  //this implies the minimum combination of rest of the change.
							for(int k = 0; k<sizeOfList; k++){
								coin_count[k] = min_coin[k];
							}
							break;
						}
				}
				if(i==0){//initialize level_min_coin
					for(int j = 0; j<sizeOfList; j++){
						level_min_coin[j] = icoin_num[j] + coin_count[j];
					}

				}else{
					for(int j = 0; j<sizeOfList; j++){
						candidate[j] = icoin_num[j] + coin_count[j];
					}

					//compare the older combined array and new combined array
					if(coin_counter(level_min_coin,sizeOfList)>coin_counter(candidate,sizeOfList)){
						for(int j = 0; j<sizeOfList; j++){
							level_min_coin[j] = candidate[j];
						}
					}
				}
			}
		}
		//save the min coin combination in this depth to min_coin 
		for(int j = 0; j<sizeOfList; j++){
			min_coin[j] = level_min_coin[j];
		}
	}
}
