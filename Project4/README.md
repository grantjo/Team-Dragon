## Project 4 - Group 34 - Team Dragon


### CS 325 Project 4: The Travelling Salesman Problem (TSP)
Authors: Mel Drews, Jordan Grant, Adrian Buenavista

There are 2 algorithms implemented in this project.

1) Nearest Neighbor with Genetic Algorithm Improvement
2) Nearest Neighbor with 2-Opt Improvement

The first is called "tsp-genetic.js" and the second is called "tsp-2opt.js"

Nodejs is a dependancy to run these algorithms.

Calling convention for 1)

node tsp-genetic.js [inputFile] [size of Population] [number of generations]

eg. node tsp-genetic.js tsp_example_1.txt 500 3000

population size = 500
number of generations = 3000

Calling convention for 2)

node tsp-2opt.js [inputFile] [size of population] [number of 2opt iterations]

eg. node tsp-2opt.js tsp_example_1.txt. 500 3000

population size = 500
number of 2 Opt Iterations  = 3000


\* while each program is running, feedback on progress will be reported to the
  console. At the end of the programs a new file will be created with the
generated solution as per assignment specifications and named: [inputFile].tour
