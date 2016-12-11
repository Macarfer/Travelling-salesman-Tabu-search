**This is a description of the Optimized Branch! If you want to see the things explained here, go there! ;)**

# Tabu search  
Tabu search algorithm following given guidelines.

## What's this?  
This is a C implementation of a **Tabu-search** algorithm for solving the  **Travelling-salesman** problem.   

## How does it work?  
Basically it works with two files:  
* A matrix where the distance between cities is stored
* A collection of random numbers (_this is used to generate an exact initial solution_)  

It can be used with or without the _randomNumbers_ file and should be called like this:  ```tabuSearch pathToDistanceMatrix [pathToRandoms]```  

## What's the output?  
The output is a set of different results that are generated during the calculation proccess it also outputs the content of the tabu list in each iteration. At the end the solution is shown as well as the iteration when it was calculated.  

## How is the solution calculated?  
1. First a greedy algorithm calculates an initial solution  
2. Each time a solution is generated, if it's better than the actual solution then it becomes the actual solution.  
3. If the solution is in the better 30 solutions, then it's added to a solutions matrix where it is inserted accordingly to it's distance. 
4. Now, for each iteration we alternate two functions  
  4.1. On even iterations a new greedy solution is generated but, this time the distance between two cities is penalized if it has been previously generated.  
  4.3. On odd iterations a random solution between the 30 better solutions is picked so it can act as the new initial solution.  
5. When the 10000 iteration is reached the program ends and shows the best solution it has found  

## How long does it take to calculate this?  
Speed is something important in this kind of algorithms that's why most of the variables are global. (_I know It looks messy but, in the end for this purpose that is the best approach_)  

If we compile it without  **gcc** optimizations it takes around 2~3 seconds (_I only measured it by hand, when I have the time I'll do it with system calls_) on a **Intel I5 2520m**
If we compile it with **gcc** optimization **-O3** it takes around 1~3 seconds (_I only measured it by hand, when I have the time I'll do it with system calls_) on a **Intel I5 2520m**
If this is compared with my own Python implementation, the increase of speed is enormous 1h20m in python and around 2 seconds here! :)  

## How good is the solution?  
Quite good I think! The solution I'm always achieving right now is 3024km. If we compare this with the initial solution proposed to me when I started this project (5891km) a clear improvement can be seen.  
