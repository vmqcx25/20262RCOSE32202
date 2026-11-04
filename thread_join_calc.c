#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 3

// Structure to pass multiple arguments to the thread function
typedef struct __myarg_t {
    int a;
    int b;
} myarg_t;

// Structure to hold the return values from the thread
typedef struct __myret_t {
    int sum;
    int prod;
} myret_t;

// Function to be executed by the thread
void *mythread(void *arg) {
    myarg_t *m = (myarg_t *) arg;
    printf("%d %d\n", m->a, m->b);                      // print args
    myret_t *r = malloc(sizeof(myret_t));               // allocate return struct
    r->sum = m->a + m->b;
    r->prod = m->a * m->b;
    return (void *) r;
}

int main(int argc, char *argv[]) {
    int rc;
    pthread_t p[NUM_THREADS];
    myarg_t args[NUM_THREADS];
    myret_t *m[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        // Arguments: (10,20), (30,40), (50,60)
        args[i].a = 10 + i * 20;
        args[i].b = 20 + i * 20;
        // Create a new thread, pass its own args to mythread function
        rc = pthread_create(&p[i], NULL, mythread, &args[i]);
        if (rc != 0) {
            fprintf(stderr, "pthread_create failed: %d\n", rc);
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        // Wait for the thread to terminate and retrieve its return value
        pthread_join(p[i], (void **) &m[i]);
        // Print the values returned by the thread (always in thread order)
        printf("returned [%d] sum=%d prod=%d\n", i, m[i]->sum, m[i]->prod);
        free(m[i]);     // release memory allocated in the thread
    }
    return 0;
}
