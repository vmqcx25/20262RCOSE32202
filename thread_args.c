#include <stdio.h>
#include <pthread.h>

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
    pthread_t p;    // Thread identifier
    int rc;         // Return to check thread creation success

    myarg_t args;   // Arguments to pass to the thread
    // Initialize the arguments
    args.a = 10;
    args.b = 20;
    // Create a new thread, passing the arguments to the mythread function
    rc = pthread_create(&p, NULL, mythread, &args);
    if (rc != 0) {
        fprintf(stderr, "pthread_create failed: %d\n", rc);
        return 1;
    }

    // Wait for the thread to finish so its output is not lost
    pthread_join(p, NULL);
    return 0;
}
