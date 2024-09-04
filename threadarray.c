// Matthew Bolding
// Operating Systems 40203 Spring 2022

#include <unistd.h>     
#include <sys/types.h>   
#include <errno.h>      
#include <stdio.h>      
#include <stdlib.h>     
#include <pthread.h>    
#include <string.h>     

// Global Variable
char *messages[] = {"Hello!", "Hi!", "Greetings!","Howdy", "What's up?", 
                    "Hola!", "Good Day!", "Hey!", "Sup!", "My man!"};

/* struct to hold data to be passed to a thread
this shows how multiple data items can be passed to a thread */
typedef struct str_thdata {
    int thread_no;
    char message[100];
} thdata;

// Thread Function Prototypes
void print_message_function(void *ptr);
void initialize_data(int num_threads, thdata *data);
void create_threads(int num_threads, pthread_t *threads, thdata *data);
void join_thread(int num_threads, pthread_t *threads);

int main(int argc, char *argv[]) {
    int num_threads;

    // Determine if the user has provided correct input.
    if(argc != 2) {
        fprintf(stderr, "threadarray usage: threadarray [number of threads]\n");
        exit(1);
    } else {
        num_threads  = atoi(argv[1]);
    }

    // Initialize two arrays of length argc containing pthread_t and thdata structs.
    pthread_t threads[num_threads];
    thdata data[num_threads];

    // Initialize, create, and finally join all the threads.
    initialize_data(num_threads, data);
    create_threads(num_threads, threads, data);
    join_thread(num_threads, threads);

    exit(0);
}

/**
* print_message_function is used as the start routine for the threads used
* it accepts a void pointer 
**/
void print_message_function(void *ptr) {
    thdata *data;            
    data = (thdata *) ptr;  /* type cast to a pointer to thdata */

    /* do the work */
    fprintf(stdout, "Thread %d says %s \n", data->thread_no, data->message);

    pthread_exit(0); /* exit */
}

/*
 * Thread to initialize all the data for each thread.
 */
void initialize_data(int num_threads, thdata *data) {
    int i;
    srand(time(NULL));
    for(i = 0; i < num_threads; i++) {
        data[i].thread_no = i + 1;
        strcpy(data[i].message, messages[rand() % 10]);
    }
}

/*
 * Thread to create all threads.
 */
void create_threads(int num_threads, pthread_t *threads, thdata *data) {
    int i;
    for(i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, (void *) &print_message_function, (void *) &data[i]);
    }
}

/*
 * Thread to join all threads.
 */
void join_thread(int num_threads, pthread_t *threads) {
    int i;
    for(i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
}