// Matthew Bolding
// Operating Systems 40203 Spring 2022

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h> 
#include <stdbool.h>

// define Values
#define ROWS 6
#define COLS 7
#define CHECK_TYPES 4

// Global Variables
char *board;
bool red = false, blue = false;

// Thread Function Prototypes
void *check_rows(void *pointer);
void *check_cols(void *pointer);
void *check_nesw(void *pointer);
void *check_nwse(void *pointer);

int main(int argc, char *argv[]){
    FILE *fd;

    // Attempt to open the file.
    if(argc == 1) {
        fprintf(stderr, "Usage: ./cfwin file\n");
        exit(1);
    } else if ((fd = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "./cfwin: File %s not found.\n", argv[1]);
        exit(1);
    }
    
    // Allocate the size of the board in memory.
    board = malloc(sizeof(char) * ROWS * COLS);

    // Load in the file to the two-dimensional array.
    int i, j;
    char buffer;
    for(i = 0; i < ROWS; i++) {
        for(j = 0; j < COLS; j++) {
            fread(&buffer, sizeof(char), 1, fd);
            // Note new lines.
            if(buffer == '\n') {
                if(i == ROWS - 1 && j == COLS -1) {
                    break;
                } else j--;
            } else {
                board[(i * COLS) + j] = buffer;
            }
        }
    }

    // Initialize, create, and join all the threads.
    pthread_t rows_t, cols_t, nesw_t, nwse_t;

    pthread_create(&rows_t, NULL, (void *) check_rows, NULL);
    pthread_create(&cols_t, NULL, (void *) check_cols, NULL);
    pthread_create(&nesw_t, NULL, (void *) check_nesw, NULL);
    pthread_create(&nwse_t, NULL, (void *) check_nwse, NULL);
   
    pthread_join(rows_t, NULL);
    pthread_join(cols_t, NULL);
    pthread_join(nesw_t, NULL);
    pthread_join(nwse_t, NULL);

    // Free the board from memory.
    free(board);

    // Print the results.
    // This assumes there's only one or no winner.s
    if(!blue && !red) {
        fprintf(stdout, "NO WINNER\n"); 
    } else {
        if(red) fprintf(stdout, "WINNER: Red\n");
        else if(blue) fprintf(stdout, "WINNER: Blue\n");
    }

    return 0;
}

/*
 * Thread to check if a winner exists on any row of the board.
 */
void *check_rows(void *pointer) {
    int i, j;
    int count = 1;
    char prev = '\n';
    char now;

    for(i = 0; i < ROWS; i++) {
        for(j = 0; j < COLS; j++) {
            prev = now;
            now = board[(i * COLS) + j];

            if(now == 'r' && prev =='r') {
                count++;
            } else if(now == 'b' && prev == 'b') {
                count++;
            } else {
                count = 1;
            }
            
            if(count == 4) {
                if(now == 'r') {
                    red = true;
                } else {
                    blue = true;
                }
            }
        }
        count = 1;
    }

    pthread_exit(0);
}

/*
 * Thread to check if a winner exists on any column of the board.
 */
void *check_cols(void *pointer) {
    int j, i;
    int count = 1;
    char prev = '\n';
    char now;

    for(j = 0; j < COLS; j++) {
        for(i = 0; i < ROWS; i++) {
            prev = now;
            now = board[(i * COLS) + j];

            if(now == 'r' && prev =='r') {
                count++;
            } else if(now == 'b' && prev == 'b') {
                count++;
            } else {
                count = 1;
            }

            if(count == 4) {
                if(now == 'r') {
                    red = true;
                } else {
                    blue = true;
                }
            }
        }
        count = 1;
    }

    pthread_exit(0);
}

/*
 * Thread to check if a winner exists on any northeast-southwest diagonal of the board.
 */
void *check_nesw(void *pointer) {
    int i, j, k;
    int count = 1;
    char prev = '\n';
    char now;

    for(k = 0 ; k <= COLS + ROWS - 2; k++) {
        for(j = 0 ; j <= k ; j++) {
            i = k - j;
            if(i < ROWS && j < COLS) {
                prev = now;
                now = board[(i * COLS) + j];

                if(now == 'r' && prev =='r') {
                    count++;
                } else if(now == 'b' && prev == 'b') {
                    count++;
                } else {
                    count = 1;
                }

                if(count == 4) {
                    if(now == 'r') {
                        red = true;
                    } else {
                        blue = true;
                    }
                }
            }
        }
        count = 1;
    }

    pthread_exit(0);
}

/*
 * Thread to check if a winner exists on any northwest-southeast diagonal of the board.
 */
void *check_nwse(void *pointer) {
    int i, j, k;
    int count = 1;
    char prev = '\n';
    char now;

    for(k = -(COLS - 1); k <= ROWS - 1; k++) {
        for(i = ROWS ; i >= k ; i--) {
            j = i - k;
            if(((i < ROWS && j < COLS) && (i >= 0 && j >= 0))) {
                prev = now;
                now = board[(i * COLS) + j];

                if(now == 'r' && prev =='r') {
                    count++;
                } else if(now == 'b' && prev == 'b') {
                    count++;
                } else {
                    count = 1;
                }

                if(count == 4) {
                    if(now == 'r') {
                        red = true;
                    } else {
                        blue = true;
                    }
                }
            }   
        }
        count = 1;
    }

    pthread_exit(0);
}