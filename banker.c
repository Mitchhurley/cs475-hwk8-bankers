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
    int** safe_seq = malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        safe_seq[i] = malloc(sizeof(int) * n);
    }
    //keep track of number of safe sequences
    int count = 0;
    //Find thread that can be finished with available reasources
    int i = 0;
    while (count < n) {
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int canExecute = 1;
                int j = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = 0;
                        break;
                    }
                }
                if (canExecute) {
                    int k = 0;
                    for (k = 0; k < m; k++) {
                        work[k] += alloc[i][k];
                    }
                    finish[i] = 1;
                    // Add thread ID to current safe sequence
                    for (k = 0; k < n; k++) {
                        safe_seq[count][k] = (k < count ? safe_seq[k][k] : -1);
                    }
                    safe_seq[count][count] = i;
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