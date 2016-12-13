#include "fileManager.h"
#include <math.h>
#include <time.h>

#define MAXITERATIONS 10000
#define TENDENCYPARAMETER 13
#define MAXITERATIONSWITHOUTIMPROVEMENT 35
#define MAX_INT 2147483647
#define BEST_SOLUTIONS_SIZE 9
#define MU 1.009

void initWithoutRandom(const char * path);
void initWithRandom(const char * path,const char * path2);
void generateInitialSolution();
void generateGreedyInitialSolution();
void run();
