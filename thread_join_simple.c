#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct __myarg_t {
    int a;
    int b;
} myarg_t;

typedef struct __myret_t {
    int sum;
    int prod;
} myret_t;

void *mythread(void *arg) {
    myarg_t *m = (myarg_t *) arg;
    printf("%d %d\n", m->a, m->b);
    myret_t *r = malloc(sizeof(myret_t));
    r->sum = m->a + m->b;
    r->prod = m->a * m->b;
    return (void *) r;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    myret_t *m;
    myarg_t args;
    args.a = 10;
    args.b = 20;

    pthread_create(&p, NULL, mythread, &args);
    pthread_join(p, (void **) &m);

    printf("returned %d %d\n", m->sum, m->prod);
    free(m);
    return 0;
}
