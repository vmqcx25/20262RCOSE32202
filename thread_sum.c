#include <stdio.h>
#include <pthread.h>

#define N 100
#define NUM_THREADS 3

// 입력(배열, 구간)과 출력(부분합)을 함께 담는 구조체
typedef struct __myarg_t {
    int id;
    int *arr;
    int start;   // 포함
    int end;     // 미포함
    long sum;    // 결과
} myarg_t;

// 스레드가 실행할 함수: [start, end) 구간의 합 계산
void *mythread(void *arg) {
    myarg_t *m = (myarg_t *) arg;
    long s = 0;
    for (int i = m->start; i < m->end; i++)
        s += m->arr[i];
    m->sum = s;
    printf("thread %d: [%d, %d) partial sum = %ld\n", m->id, m->start, m->end, s);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p[NUM_THREADS];
    myarg_t args[NUM_THREADS];
    int arr[N];
    int rc;

    for (int i = 0; i < N; i++)
        arr[i] = i + 1;   // 1..100

    int chunk = N / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].id = i;
        args[i].arr = arr;
        args[i].start = i * chunk;
        // 마지막 스레드가 나머지(100 % 3)를 맡는다
        args[i].end = (i == NUM_THREADS - 1) ? N : (i + 1) * chunk;
        args[i].sum = 0;
        rc = pthread_create(&p[i], NULL, mythread, &args[i]);
        if (rc != 0) {
            fprintf(stderr, "pthread_create failed: %d\n", rc);
            return 1;
        }
    }

    long total = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(p[i], NULL);
        total += args[i].sum;
    }

    printf("total = %ld (expected 5050)\n", total);
    return 0;
}
