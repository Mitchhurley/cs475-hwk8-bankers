#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

// TODO - Safety Algorithm goes here
//N is num processes
//M is reasource types
void isSafe(int* available, int** alloc, int** need, int m, int n){
    //Create the work vector from available
    int* work = vec_clone(available, m);
    //init finish array
    int* finish = malloc(sizeof(int) * n);
    //keep track of safe sequence
    int* safe_seq = malloc(sizeof(int) * n);
    
    int seq_top = -1;
    //keep track of number of safe sequences
    int count = 0;
    //Find thread that can be finished with available reasources
    int i = 0;
    int seq_pos = 0;
    //do this until all are found
    while(count<(n * n)) {
        print("Current Finish: " + print_vec(finish, n) + "\n");
        for (i = 0; i < n; i++) {
            //loops through to find unfinished thread
            if (finish[i] == 0) {
                //now we found the thread, lets loop through its needs to make sure they are met
                int canExecute = 1;
                int j = 0;
                print("Thread "+ i + " is unfinished, testing to see if reasources can be allocated\n");
                for (j = 0; j < m; j++) {
                    //for each need of the thread, check if we have the reasources
                    if (need[i][j] > work[j]) {
                        //if it cant be met, set cant execute to false
                        canExecute = 0;
                        print("Thread "+ i + " cant finish because reasource " + j " is needed\n");
                    }
                }
                if (canExecute) { 
                    print("Thread "+ i + " can finish, freeing reasources\n");
                    int k = 0;
                    print("prev work" + print_vec(work[k], m)+ "\n");
                    for (k = 0; k < m; k++) {
                        //simulate freeing of reasources
                        work[k] += alloc[i][k];
                    }
                    //set the finish value for the thread to true
                    print("curr work work" + print_vec(work[k], m)+ "\n");
                    finish[i] = 1;
                    // Add thread ID to current safe sequence
                    safe_seq[count][seq_pos++] = i;
                    
                    if (count == 0 || safe_seq[count][n-1] != -1) {
                        // If current safe sequence is complete, increment number of schedules found
                        count++;
                        // If there are more safe sequences, move to the next row of safe_seq
                        if (count < n) {
                            for (k = 0; k < n; k++) {
                                safe_seq[count][k] = safe_seq[count-1][k];
                            }
                        }
                    }
                    
                }
            }
        }
    }

    // print all safe schedules
    if (count == n) {
        print_schedules(finish, safe_seq, count, n);
    } else {
        printf("UNSAFE: ");
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                printf("T%d ", i);
            }
        }
        printf("cannot finish.\n");
    }
    free(finish);
    for (int i = 0; i < n; i++){
        free(safe_seq[i]);
    }
    free(safe_seq);
    free(work);
}

void print_schedules(int* finish, int** sequences, int count, int n) {
    int i; 
    int j;
    int k;
    int* schedule = malloc(sizeof(int) * n);
    for (i = 0; i < count; i++) {
        int* sequence = sequences[i];
        int count = 0;
        for (j = 0; j < n; j++) {
            if (finish[sequence[j]] == 0) {
                continue;
            }
            for (k = 0; k < count; k++) {
                if (schedule[k] == sequence[j]) {
                    break;
                }
            }
            if (k < count) {
                continue;
            }
            schedule[count] = sequence[j];
            count++;
        }
        if (count == n) {
            printf(" ");
            for (j = 0; j < n; j++) {
                printf("T%d ", schedule[j]);
            }
            printf("\n");
        }
    }
    free(schedule);
}
int ** subtractMatrices(int** matrix1, int** matrix2, int outerLength, int innerLength){
    int** diffMatrix = (int**)malloc(sizeof(int*)*outerLength);
    for(int i = 0;i<outerLength;i++){
        diffMatrix[i] = (int*)malloc(sizeof(int)*innerLength);
        for(int j =0; j<innerLength;j++){
            diffMatrix[i][j] = matrix1[i][j]-matrix2[i][j];
        }
    }
    return diffMatrix;
}

void isSafe2(int* available, int** alloc, int** need, int m, int n){
    //Create the work vector from available
    int* work = vec_clone(available, m);
    //init finish array
    int* finish = malloc(sizeof(int) * n);
    //keep track of safe sequence
    int* safe_seq = malloc(sizeof(int) * n);
    if(recursive_test(work, alloc, need, m, n, 0, finish, safe_seq)){
        //safe
    }else{
        //print unsafe stuff
    }
}

bool recursive_test(int* available, int** alloc, int** need, int m, int n, int depth, int* finished,  int* cur_seq){
    //Create the work vector from available
    int* work = vec_clone(available, m);
    //init finish array from the passed one
    int* finish = vec_clone(finished, n);;
    //keep track of safe sequence
    int* safe_seq = vec_clone(cur_seq, n)
    for (i = 0; i < n; i++) {
            //loops through to find unfinished thread
            if (finish[i] == 0) {
                int j = 0;
                for (j = 0; j < m; j++) {
                    //for each need of the thread, check if we have the reasources
                    if (need[i][j] > work[j]) {
                        //if it cant be met, set cant execute to false
                        free(finish);
                        free(safe_seq);
                        free(work);
                        break;
                    }
                }
                for (k = 0; k < m; k++) {
                    //simulate freeing of reasources
                    work[k] += alloc[i][k];
                }
                //set the finish value for the thread to true
                finish[i] = 1;
                safe_seq[depth] = i;
                //if this isnt the last process, recurse
                if (depth != n){
                    if (recursive_test(work, alloc, need, m, n, depth + 1, finish, safe_seq)){
                        free(finish);
                        free(safe_seq);
                        free(work);
                        return true;
                    }
                }else {
                    //print the current schedule then return true
                }
            }
    }
}