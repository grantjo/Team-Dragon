Project 2 - Group 34 - Team Dragon

Authors: Mel Drews, Inhyuk Lee, Jordan Grant

Solutions for the Making Change Problem.  Implementation and analysis of three algorithms.

1. Brute Force/ D&C
2. Dynamic Programming
3. Greedy Algorithm

###Preprocessor Definitions:

* There is a single preprocessor definition that will modify the input and output of the programs

	```c++
	#define WRITETOFILE
	```

* if WRITETOFILE is defined the program will read the arrays from an inputfile and write the output to an output file 

* if WRITETOFILE is not defined the program will read the arrays from an inputfile and write the output to the console along with the time it took to run each call to 'makeChange' in nanoseconds.


###Building Solutions on OSU Flip Server:


use included Makefile with the following commands:

* make with no arguments will build all solutions
	* make

* build change_slow.cc named change_slow
	* make change_slow

* build change_dp.cc named change_dp
	* make change_dp

* build change_greedy.cc named change_greedy
	* make change_greedy



###Running The Programs, command line arguments:

* If WRITETOFILE is defined the program will expect the first argument to be the name of the inputfile and the second to be the name of the output file
	* Expected input format
	```
	[v1, v2, v3, v4]
	A
	```

example change_slow on flip:  
make change_slow  
enumeration Coin1.txt Coin1Change.txt  

* If WRITETOFILE is commented the program expects a single argument for the name of the inputfile.
	* Expected input format
	```
	[v1, v2, v3, v4, ..., vn]
	[A1, A2, A3, ..., An]
	```

example change_slow on flip:  
make change_slow  
change_slow report Q3.txt 


