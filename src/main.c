#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tabuSearch.h"
#include <sys/time.h>

int main(int argc, char const *argv[]) {
struct timeval firstTime, lastTime;
double totalTime,durationGetTime;

  switch (argc){
    case 2:
    gettimeofday(&firstTime,NULL);
    gettimeofday(&lastTime,NULL);
    durationGetTime = (lastTime.tv_sec-firstTime.tv_sec+(lastTime.tv_usec-firstTime.tv_usec)/1.e6);
    gettimeofday(&firstTime,NULL);
    initWithoutRandom(argv[1]);
    generateGreedyInitialSolution();
    // generateInitialSolution();
    run();
    gettimeofday(&lastTime,NULL);
    totalTime=(lastTime.tv_sec-firstTime.tv_sec+(lastTime.tv_usec-firstTime.tv_usec)/1.e6)-durationGetTime;
    printf("Total time: %lfs\n",totalTime);
    break;
    case 3:

    initWithRandom(argv[1],argv[2]);
    generateInitialSolution();
    //generateInitialSolution();
    run();
    break;
    default:
      printf("Error on function usage!\n Usage:\ttabuSearch pathToDistancesFile [pathToRandomNumbers]\n");
    break;
  }
}
