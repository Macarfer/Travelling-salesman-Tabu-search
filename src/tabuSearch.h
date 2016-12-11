#include "fileManager.h"
#include <math.h>
#include <time.h>

#define MAXITERATIONS 10000
#define TENDENCYPARAMETER 12
#define MAXITERATIONSWITHOUTIMPROVEMENT 20
#define MAX_INT 2147483647
#define BEST_SOLUTIONS_SIZE 30
#define MU 5000

void initWithoutRandom(const char * path);
void initWithRandom(const char * path,const char * path2);
void generateInitialSolution();
void generateGreedyInitialSolution();
void run();
