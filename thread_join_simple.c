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
    pthread_t p[3];
    myarg_t args[3];
    myret_t *m[3];

    for (int i = 0; i < 3; i++) {
        args[i].a = 10 + i * 20;
        args[i].b = 20 + i * 20;
        pthread_create(&p[i], NULL, mythread, &args[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(p[i], (void **) &m[i]);
        printf("returned %d %d\n", m[i]->sum, m[i]->prod);
        free(m[i]);
    }
    return 0;
}
