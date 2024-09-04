// Matthew Bolding
// Operating Systems 40203 Spring 2022

#include <stdio.h>
#include <pthread.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Global Variable
int number;

// Thread Function Prototypes
void *negative(void *pointer);
void *zero(void *pointer);
void *one(void *pointer);
void *prime(void *pointer);
void *even(void *pointer);
void *odd(void *pointer);

// Function Prototype
bool is_prime(int n);

int main(int argc, char *argv[]){
    // Check for valid user input
    if(argc == 1) {
        fprintf(stderr, "Usage: ./numbers number ...\n");
        exit(1);
    }

    int i;
    pthread_t negative_t, zero_t, one_t, prime_t, even_t, odd_t;

    // Iterate through each number entered.
    for(i = 1; i < argc; i++) {
        number = atoi(argv[i]);

        // And create threads for each check for each number.
        pthread_create(&negative_t, NULL, (void *) negative, NULL);
        pthread_create(&zero_t, NULL, (void *) zero, NULL);
        pthread_create(&one_t, NULL, (void *) one, NULL);
        pthread_create(&prime_t, NULL, (void *) prime, NULL);
        pthread_create(&even_t, NULL, (void *) even, NULL);
        pthread_create(&odd_t, NULL, (void *) odd, NULL);
   
        pthread_join(negative_t, NULL);
        pthread_join(zero_t, NULL);
        pthread_join(one_t, NULL);
        pthread_join(prime_t, NULL);
        pthread_join(even_t, NULL);        
        pthread_join(odd_t, NULL);
    }

    return 0;
}

/*
 * Thread to check the number is negative.
 */
void *negative(void *pointer) {
    if(number < 0) fprintf(stdout, "NEG:%13d\n", number);

    pthread_exit(0);
}

/*
 * Thread to check the number is zero.
 */
void *zero(void *pointer) {
    if(number == 0) fprintf(stdout, "ZERO:%12d\n", number);

    pthread_exit(0);
}

/*
 * Thread to check the number is one.
 */
void *one(void *pointer) {
    if(number == 1) fprintf(stdout, "ONE:%13d\n", number);

    pthread_exit(0);
}

/*
 * Thread to check the number is prime.
 */
void *prime(void *pointer) {
    if(is_prime(number)) fprintf(stdout, "PRIME:%11d\n", number);

    pthread_exit(0);
}

/*
 * Thread to check the number is even and greater than 0.
 */
void *even(void *pointer) {
    if(number % 2 == 0 && number > 0) fprintf(stdout, "EVEN:%12d\n", number);

    pthread_exit(0);
}

/*
 * Thread to check the number is odd, greater than 1, and not prime.
 */
void *odd(void *pointer) {
    if(number > 1 && number % 2 != 0 && !is_prime(number)) fprintf(stdout, "ODD:%13d\n", number);

    pthread_exit(0);
}

/*
 * Function to determine whether a number is prime.
 */
bool is_prime(int n) {
    int i;

    if(n < 2) return false;

    for(i = 2; i <= sqrt(n); i++) {
        if(n % i == 0) {
            return false;
        }
    }

    return true;
}