#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define NUM_THREADS   5

void *print_hello(void *threadid) {
        long tid; //Variable for thrad ID
        tid = (long)threadid; //Assigns thread ID to tid
        printf("Hello World! Thread %ld!\n", tid); //Prints Hello World and thread ID
        pthread_exit(NULL);//Exits the current thread
}

int main(int argc, char const *argv[]) {
        pthread_t threads[NUM_THREADS]; //Creates and array of threads of size NUM_THREADS
        int rc;//initialize return code variable
        long t;//initialize counter variable for loop
        for(t = 0; t < NUM_THREADS; t++) {
                printf("In main: creating thread %ld\n", t);//Prints that it is creating thread with ID
                rc = pthread_create(threads + t, NULL, print_hello, (void *) t); //Creates thread with driver method
                if(rc) {//Checks for error
                        printf("ERROR : return code is %d\n", rc); //Prints that there is an error with return code
                        exit(-1); //Sends exit signal
                }
        }

        /*Wait for all threads to complete*/
        for(t=0; t < NUM_THREADS; t++){
            pthread_join(threads[t], NULL);
        }

      pthread_exit(NULL); //Exits thread
        return 0;
}
