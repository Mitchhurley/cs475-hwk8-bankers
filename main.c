#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

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
  
  // TODO: Run banker's safety algorithm

  return 0;
}