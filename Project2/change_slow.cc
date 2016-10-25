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
** Authors: Inhyuk Lee
** File: changeslow.cc
** Description: An implementation of the make change problem using Recursion or brue 
**              force
                
**************************************************************************************/
//#include<chrono>
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
*Function: combine
*Paramaters: two array that you want to combine
*Return: combined array.
*Description: This function will combine the two array into one and return it.
*/
int* combine(int* a, int* b, int sizeOfList);
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
*Paramaters: list of coins (int array), and int value that you want for change.
*Return: array of int which indecates the each number of coins.
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
int* changeslow(int* V,int A, int sizeOfList);

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
			int* coins = changeslow(list,iChange,sizeOfList);
			cout <<"coins"<<"|"<<"number of coins"<<endl;
			for(int i = 0; i<sizeOfList; i++){
				cout <<list[i]<<"       "<<coins[i]<<endl;
			}
			int num = coin_counter(coins,sizeOfList);
			cout << "The number of coins we used: "<<num<<endl;
			delete[] list;
			delete[] coins;
		}
	}
	#else
		ofstream outputFile;
		outputFile.open(outputFileName.c_str());
		
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
				int* coins = changeslow(list,iChange,sizeOfList);
				int num = coin_counter(coins,sizeOfList);
				outputFile << "[";
				for(int i =0; i<sizeOfList; i++){
					if(i+1==sizeOfList)
						outputFile << coins[i];
					else
						outputFile << coins[i] << ", ";
				}
				outputFile << "]\n" << num << "\n\n";
				delete[] list;
				delete[] coins;
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

int* combine(int* arrayOne, int* arrayTwo, int sizeOfList){
	int* combinedArray = new int[sizeOfList];
	for(int i = 0; i<sizeOfList; i++){
		combinedArray[i]=arrayOne[i]+arrayTwo[i];
	}
	delete[] arrayOne;
	delete[] arrayTwo;
	return combinedArray;
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
 
int* changeslow(int* V,int A, int sizeOfList){
	//check the existence of coin that match the change
	//or check if the change is 0
	if(existence(V,A,sizeOfList)>=0||A==0){
		int* coin_count = new int[sizeOfList];
		for(int i = 0; i<sizeOfList; i++){
			coin_count[i]=0;
		}
		if(A!=0){ //count the matching change
			coin_count[existence(V,A,sizeOfList)]=1;
		}
		return coin_count;
	}else{
		int* coin_count;
		int* temp;
		int* temp2;
		for(int i = 0; i<sizeOfList; i++){
			if(V[i]>A){ //if the coin is bigger than the change skip it.
				
			}else{
				//add the ith coin 
				int* icoin = changeslow(V,V[i],sizeOfList);
				//find rest of the combination
				int* restofcoins = changeslow(V,A-V[i],sizeOfList);
				if(i==0){
					coin_count = combine(icoin,restofcoins,sizeOfList);
				}else{
					temp = combine(icoin,restofcoins,sizeOfList);
					//compare the older combined array and new combined array
					if(coin_counter(coin_count,sizeOfList)>coin_counter(temp,sizeOfList)){
						temp2 = coin_count;
						coin_count = temp;
						delete[] temp2;
					}
				}
			}
		}
		return coin_count;
	}
}
