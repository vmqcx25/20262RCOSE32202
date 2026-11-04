#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 3

// Define a structure to pass multiple arguments to the thread
typedef struct __myarg_t {
    int a;
    int b;
} myarg_t;

// Function to be executed by the thread
void *mythread(void *arg) {
    myarg_t *m = (myarg_t *) arg;
    // Print the values of the arguments passed to the thread
    printf("%d %d\n", m->a, m->b);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p[NUM_THREADS];   // Thread identifiers
    myarg_t args[NUM_THREADS];  // Arguments to pass to each thread
    int rc;                     // Return to check thread creation success

    for (int i = 0; i < NUM_THREADS; i++) {
        // Initialize the arguments: (10,20), (30,40), (50,60)
        args[i].a = 10 + i * 20;
        args[i].b = 20 + i * 20;
        // Create a new thread, passing its own arguments to mythread
        rc = pthread_create(&p[i], NULL, mythread, &args[i]);
        if (rc != 0) {
            fprintf(stderr, "pthread_create failed: %d\n", rc);
            return 1;
        }
    }

    // Wait for all threads to finish so their output is not lost
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(p[i], NULL);
    return 0;
}
