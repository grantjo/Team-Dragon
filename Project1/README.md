Project 1 - Team Dragon

Authors: Mel Drews, Jordan Grant

Solutions to the maximum sub-array problem. Implementation and analysis of four solutions.

1. Enumeration
2. Optimized Enumeration
3. Divide and Conquer
4. Linear Time

Building Solutions on OSU Flip Server:

use included Makefile with the following commands:

* make with no arguments will build all solutions
	* make

* build enumeration.cc named enumeration
	* make enumeration

* build better_enumeration.cc named better_enumeration
	* make better_enumeration

* build divide_and_conquer.cc named divide_and_conquer
	* make divide_and_conquer

* build linear_time.cc named linear_time
	* make linear_time

Preprocessor Definitions:

* There is a single preprocessor definition that will modify the runtime of the program.

	#define WRITETOFILE

* if WRITETOFILE is defined the program will read the arrays from an inputfile and write the output to an output file 

* if WRITETOFILE is not defined the program will read the arrays from an inputfile and write the output to the console along with the time it took to run each call to MaximumSub in nanoseconds.


Running The Programs, command line arguments:

* If WRITETOFILE is defined the program will expect the first argument to be the name of the inputfile and the second to be the name of the output file
* If WRITETOFILE is commented the program expects a single argument for the name of the inputfile.


