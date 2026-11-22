#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE 5
#define TASKS 10

int buf[SIZE], in = 0, out = 0, count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    for (int i = 1; i <= TASKS; i++) {
        pthread_mutex_lock(&lock);
        while (count == SIZE) {
            pthread_cond_wait(&not_full, &lock);
        }
        buf[in] = i;
        in = (in + 1) % SIZE;
        count++;
        printf("Produced task %d\n", i);
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 1; i <= TASKS; i++) {
        pthread_mutex_lock(&lock);
        while (count == 0) {
            pthread_cond_wait(&not_empty, &lock);
        }
        int task = buf[out];
        out = (out + 1) % SIZE;
        count--;
        printf("Consumed task %d\n", task);
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&lock);
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t p, c;

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);

    printf("All tasks completed.\n");
    return 0;
}