#include "fileManager.h"
#include <math.h>
#include <time.h>

#define MAXITERATIONS 10000
#define TENDENCYPARAMETER 100
#define MAXITERATIONSWITHOUTIMPROVEMENT 100

void initWithoutRandom(const char * path);
void initWithRandom(const char * path,const char * path2);
void generateInitialSolution();
void run();
