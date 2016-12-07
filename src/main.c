#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tabuSearch.h"

int main(int argc, char const *argv[]) {
  switch (argc){
    case 2:
    initWithoutRandom(argv[1]);
    generateGreedyInitialSolution();
    run();
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
