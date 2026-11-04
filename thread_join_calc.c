#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

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
    pthread_t p;
    myret_t *m;

    myarg_t args;
    args.a = 10;
    args.b = 20;

    // Create a new thread, pass the args to mythread function
    rc = pthread_create(&p, NULL, mythread, &args);
    if (rc != 0) {
        fprintf(stderr, "pthread_create failed: %d\n", rc);
        return 1;
    }

    // Wait for the thread to terminate and retrieve its return value
    pthread_join(p, (void **) &m);

    // Print the values returned by the thread
    printf("returned sum=%d prod=%d\n", m->sum, m->prod);
    free(m);    // release memory allocated in the thread
    return 0;
}
