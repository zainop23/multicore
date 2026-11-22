#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *arg) {
    long id = (long)arg;
    pthread_mutex_t *first = (id == 0) ? &m1 : &m2;
    pthread_mutex_t *second = (id == 0) ? &m2 : &m1;

    pthread_mutex_lock(first);
    sleep(1);

    printf("Thread %ld: Waiting for lock %d...\n", id, id == 0 ? 2 : 1);

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += 2;

    int res = pthread_mutex_timedlock(second, &ts);

    if (res == 0) {
        printf("Thread %ld: Acquired lock %d.\n", id, id == 0 ? 2 : 1);
        pthread_mutex_unlock(second);
    } else if (res == ETIMEDOUT) {
        printf("Thread %ld: Timeout! Releasing lock %d.\n", id, id == 0 ? 1 : 2);
    }

    pthread_mutex_unlock(first);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, worker, (void *)0);
    pthread_create(&t2, NULL, worker, (void *)1);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}