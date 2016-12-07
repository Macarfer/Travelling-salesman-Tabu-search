#include "tabuSearch.h"
#define MAX_INT 2147483647


int distanceMatrix[DIMENSION][DIMENSION];
int swapMatrix[DIMENSION-1];
int actualSolution[DIMENSION+1];
int tabuMatrix[TENDENCYPARAMETER][TENDENCYPARAMETER]={0};
int tabuList[TENDENCYPARAMETER][2];
int bestNeighbor[DIMENSION+1];
int solution[DIMENSION+1];
int solIterations=0;
int iteration0Distance=0;
int iterationsWithoutImprovement=0;
int iterations=0;
int bestIndex0;
int bestIndex1;
int numberOfCities;
int actualDistance;
int newDistance=0;
int solutionNumber;
int swapArrayCount;
int swapArrayDimension=0;
int minimalDistance;
int restart = 1;
int tabuCount=0;

short activatedRandoms=-1;
double * randoms;
short actualRandom=-1;

void printMatrix();
float calculateRandom();
short isvalueinarray(int val, int *arr, int size);
void printActualSolution();
void calculateInitialDistance();
int * swap(int * returnVector,int * vector,int index0,int index1);
void copyArray(int * hostArray, int * array,int size);
void reorganizeTabuList();
void printTabuList();
void clearTabuList();
void calculateNeighbors();
void reinitializeTabuMatrix();
void printArray(int * array,int size);

void run(){
  printf("RECORRIDO INICIAL\n");
  printActualSolution();
  printf("\tCOSTE (km): %d\n\n",newDistance);
  calculateNeighbors();
  printf("\nMEJOR SOLUCION: \n");
  copyArray(actualSolution,solution,numberOfCities);
  printActualSolution();
  printf("\tCOSTE (km): %d\n\tITERACION: %d\n",minimalDistance,solIterations);

}
void initWithoutRandom(const char * path){

    openFile(path,distanceMatrix);
    numberOfCities=DIMENSION-1;

}

void initWithRandom(const char *path,const char * pathToRandom){
  openFile(path,distanceMatrix);
  numberOfCities=DIMENSION-1;
  randoms=openRandoms(pathToRandom);
  activatedRandoms=1;
}

void generateInitialSolution(){
int index=1,i,actualValue;
actualSolution[0]=0;
  for(;index<numberOfCities+1;){
    actualValue = 1 + floor(calculateRandom()*numberOfCities);
    for(;isvalueinarray(actualValue,actualSolution,numberOfCities);){
      actualValue+=1;
      actualValue=fmod(actualValue,numberOfCities+1);
    }
    actualSolution[index]=actualValue;
    index+=1;
  }
  actualSolution[DIMENSION]=0;
solutionNumber+=1;
calculateInitialDistance();
}


void calculateInitialDistance(){
  int i=0,index01=0,index02=0;
  actualDistance=distanceMatrix[0][actualSolution[1]];
  for(i=1;i<=numberOfCities;i++){
    index01=actualSolution[i];
    index02=actualSolution[i+1];
    actualDistance+=distanceMatrix[index01][index02];
  }
  newDistance=actualDistance;
  minimalDistance=actualDistance;
}

int calculateDistance(int * vector){
  /*Modificala para sumar en funcion da distancia previa*/
  int i=0,index01=0,index02=0;
  newDistance=distanceMatrix[0][vector[0]];
  for(i=0;i<(numberOfCities-1);i++){
    index01=vector[i];
    index02=vector[i+1];
    newDistance+=distanceMatrix[index01][index02];
  }
  newDistance+=distanceMatrix[0][vector[numberOfCities-1]];
  return newDistance;
}

int calculateDistanceOptimized(int * vector,int index0,int index1){
  newDistance=iteration0Distance;

  newDistance-=distanceMatrix[vector[index0]][vector[index0-1]];

  newDistance-=distanceMatrix[vector[index0]][vector[index0+1]];

  newDistance-=distanceMatrix[vector[index1]][vector[index1-1]];

  newDistance-=distanceMatrix[vector[index1]][vector[index1+1]];
  vector[index1]=actualSolution[index0];
  vector[index0]=actualSolution[index1];

  newDistance+=distanceMatrix[vector[index0]][vector[index0-1]];
  newDistance+=distanceMatrix[vector[index0]][vector[index0+1]];
  newDistance+=distanceMatrix[vector[index1]][vector[index1-1]];

  newDistance+=distanceMatrix[vector[index1]][vector[index1+1]];


  return newDistance;
}

void calculateNeighbors(){
  int line=0,index0,index1,jump,first;//vector[DIMENSION+1]={0};
  int * vector=malloc(sizeof(int)*(DIMENSION));
  iteration0Distance=actualDistance;
  vector[0]=0;
  vector[DIMENSION]=0;
  copyArray(vector,actualSolution,DIMENSION);
  copyArray(bestNeighbor,actualSolution,DIMENSION);

  for(;line<MAXITERATIONS;){
     index0=1;
     index1=1;
     line++;
     jump=1;
     first=0;
     iteration0Distance=actualDistance;
     for(;index0<=numberOfCities && index1<=(numberOfCities);){
       if (jump==index1){
         index0++;
         index1=1;
         jump++;
       }
       if(index0!=index1 && !tabuMatrix[index0][index1]){
         if(calculateDistanceOptimized(vector,index0,index1) < actualDistance || !first){
          first++;
          actualDistance=newDistance;
          bestIndex0=index0;
          bestIndex1=index1;
       }
       vector[index1]=actualSolution[index1];
       vector[index0]=actualSolution[index0];
     }
       index1++;
     }
     iterations++;

     bestNeighbor[bestIndex0]=actualSolution[bestIndex1];
     bestNeighbor[bestIndex1]=actualSolution[bestIndex0];
     copyArray(actualSolution,bestNeighbor,DIMENSION);
     copyArray(vector,actualSolution,DIMENSION);
     if(actualDistance < minimalDistance){
      copyArray(solution,actualSolution,DIMENSION);
      solIterations=iterations;
      minimalDistance=actualDistance;
      iterationsWithoutImprovement=0;
     }else{
       iterationsWithoutImprovement++;
     }

     /*===============================================*/
     /*               print zone                      */
     /*===============================================*/
     printf("ITERACION: %d\n\tINTERCAMBIO: (%d, %d)\n",iterations,bestIndex0-1,bestIndex1-1);
     printActualSolution();
     printf("\tCOSTE (km): %d\n\tITERACIONES SIN MEJORA: %d\n\tLISTA TABU:\n",actualDistance,iterationsWithoutImprovement);
     if(tabuCount >= TENDENCYPARAMETER){
      tabuMatrix[tabuList[0][0]][tabuList[0][1]]=0;
      tabuMatrix[tabuList[0][1]][tabuList[0][0]]=0;
      reorganizeTabuList();
      tabuCount--;
     }
     if(!tabuMatrix[bestIndex0][bestIndex1]){
       tabuMatrix[bestIndex0][bestIndex1]=1;
       tabuMatrix[bestIndex1][bestIndex0]=1;
       tabuList[tabuCount][0]=bestIndex0;
       tabuList[tabuCount][1]=bestIndex1;
     }
     tabuCount++;

     printTabuList();
     if(iterationsWithoutImprovement == MAXITERATIONSWITHOUTIMPROVEMENT){
      printf("\n***************\nREINICIO: %d\n***************\n",restart);
       clearTabuList();
       iterationsWithoutImprovement=0;
       copyArray(actualSolution,solution,DIMENSION);
       copyArray(vector,solution,DIMENSION);
       copyArray(bestNeighbor,solution,DIMENSION);
       actualDistance=minimalDistance;
       tabuCount=0;
       restart+=1;
       reinitializeTabuMatrix();
     }
     printf("\n");
  }
}

/*Auxiliar functions*/

int * swap(int * returnVector,int * vector,int index0,int index1){
  returnVector[index0] = vector[index1];
  returnVector[index1] = vector[index0];
  swapArrayCount++;
  return returnVector;

}
short isvalueinarray(int val, int *arr, int size){
    int i;
    for (i=0; i < size; i++) {
        if (arr[i] == val)
            return 1;
    }
    return 0;
}

void copyArray(int * hostArray,int * array,int size){
  int i=0;
  for(i=0;i<=size;i++)
    hostArray[i]=array[i];
}

float calculateRandom(){
  if(activatedRandoms<0){
    srand(time(NULL)*rand());
    return ((float)rand())/RAND_MAX;
  }
  actualRandom++;
  return randoms[actualRandom];
}


void reorganizeTabuList(){
  int i;
  for(i=1;i<TENDENCYPARAMETER;i++){
    tabuList[i-1][0]=tabuList[i][0];
    tabuList[i-1][1]=tabuList[i][1];
  }
}
void clearTabuList(){
  int i;
  for(i=0;i<tabuCount;i++){
    tabuList[i][0]='\0';
    tabuList[i][1]='\0';
  }
}

void reinitializeTabuMatrix(){
  int i=0,j=0;
  for(i=0;i<TENDENCYPARAMETER;i++)
    for(j=0;j<TENDENCYPARAMETER;j++)
      tabuMatrix[i][j]=0;
}
/*Print zone*/
void printTabuList(){
  int i;
  for(i=0;i<tabuCount;i++){
    printf("\t%d %d\n",tabuList[i][0]-1,tabuList[i][1]-1);
  }
}
void printMatrix(){
  int i,j;
  for (i=0;i<DIMENSION;i++) {
    for(j=0;j<i;j++){
    printf("%d ",*(distanceMatrix+i*j+j));
  }
    printf("\n");
  }
}

void printActualSolution(){
  int i;
  printf("\tRECORRIDO: ");
  for(i=1;i<=numberOfCities;i++)
    printf("%d ",actualSolution[i]);
  printf("\n");
}

void printArray(int * array,int size){
  int i;
  printf("\tRECORRIDO: ");
  for(i=0;i<=size;i++)
    printf("%d ",array[i]);
  printf("\n");
}
