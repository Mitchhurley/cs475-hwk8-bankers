#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

void endAndFree(int error, int numResources, int numProcesses, int**maxDemandMatrix,int** allocationMatrix, int*totalResourceVector){
  for(int i = 0; i <numProcesses;i++){
    free(maxDemandMatrix[i]);
    maxDemandMatrix[i] = NULL;
    free(allocationMatrix[i]);
    allocationMatrix[i]=NULL;
  }
  free(maxDemandMatrix);
  maxDemandMatrix = NULL;
  free(allocationMatrix);
  allocationMatrix = NULL;
  free(totalResourceVector);
  totalResourceVector = NULL;
  if(error==1){
    exit(1);
  }
  return;
}

int main(int argc, char *argv[])
{
  // TODO: attempt to open scenario file and scan data into allocated structures
  if(argc!=2){
    printf("Incorrect number of arguments given, program is exitting\n");
    exit(1);
  }
  FILE * pFile;
  pFile = fopen(argv[1],"r");
  if(pFile ==NULL){
    printf("This file could not be found. Exitting.\n");
    exit(1);
  }
  int numResources;
  int numProcesses;
  fscanf(pFile,"%d",&numResources);
  fscanf(pFile,"%d",&numProcesses);
  
  int* totalResourceVector = (int*)malloc(sizeof(int)*numResources);
  int** maxDemandMatrix = (int**)malloc(sizeof(int*)*numProcesses);
  int** allocationMatrix = (int**)malloc(sizeof(int*)*numProcesses);
  int error = 0;
  for(int i = 0;i<numResources;i++){
    int totalResource;
    fscanf(pFile,"%d\n",&totalResource);
    totalResourceVector[i] =totalResource;
  }
  for(int i = 0;i<numProcesses;i++){
    maxDemandMatrix[i] = (int*)malloc(sizeof(int)*numResources);
        allocationMatrix[i] = (int*)malloc(sizeof(int)*numResources);
    for(int j = 0;j<numResources;j++){
      int maxDemand;
      fscanf(pFile,"%d\n",&maxDemand);
      maxDemandMatrix[i][j] = maxDemand;
    }
  }
  for(int i = 0;i<numProcesses;i++){
    for(int j = 0;j<numResources;j++){
      int allocation;
      fscanf(pFile,"%d\n",&allocation);
      if(error==0 && allocation>totalResourceVector[j]){
        printf("Integrity test failed: allocated resources exceed total resources\n");
        error = 1;
      }
      if(error==0 && allocation>maxDemandMatrix[i][j]){
        int diff = maxDemandMatrix[i][j]-allocation;
        printf("Integrity test failed: allocated resources exceed demand for thread %d\n",i);
        printf("Need %d instances of resource %d",diff,j);
        error = 1;
      }
      allocationMatrix[i][j] = allocation;
    }
  }
  fclose(pFile);
  if(error==1){
    endAndFree(error,numResources,numProcesses,maxDemandMatrix,allocationMatrix,totalResourceVector);
  }
  int** needMatrix = subtractMatrices(maxDemandMatrix, allocationMatrix, numProcesses, numResources);
  //isSafe(totalResourceVector, allocationMatrix,numResources,numProcesses);
  // TODO: Run banker's safety algorithm
  printf("%d",isSafe(totalResourceVector,allocationMatrix,needMatrix,numResources,numProcesses));
  for(int i=0;i<numProcesses;i++){
    free(needMatrix[i]);
    needMatrix[i]=NULL;
  }
  free(needMatrix);
  needMatrix =NULL;
  endAndFree(0,numResources,numProcesses,maxDemandMatrix,allocationMatrix,totalResourceVector);
  return 0;
}