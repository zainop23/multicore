#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 4
#define TASKS 10

int q[N][TASKS], sz[N];
pthread_mutex_t lock[N];

int pop(int id) {
    int task = -1;

    pthread_mutex_lock(&lock[id]);
    if (sz[id] > 0) {
        task = q[id][--sz[id]];
    }
    pthread_mutex_unlock(&lock[id]);

    return task;
}

void *worker(void *arg) {
    long id = (long)arg;

    while (1) {
        int task = pop(id);
        for (int i = 0; task == -1 && i < N; i++) {
            if (i != id && (task = pop(i)) != -1) {
                printf("Thread %ld stole task %d from Thread %d\n",
                       id, task, i);
            }
        }
        if (task == -1) {
            break;
        }
        printf("Thread %ld processing task %d\n", id, task);
        sleep(1);
    }

    return NULL;
}

int main() {
    pthread_t t[N];

    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&lock[i], NULL);
    }

    for (int i = 1; i <= TASKS; i++) {
        int owner = (i <= 7) ? 0 : i - 7;
        q[owner][sz[owner]++] = i;
    }

    for (long i = 0; i < N; i++) {
        pthread_create(&t[i], NULL, worker, (void *)i);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(t[i], NULL);
    }

    printf("All tasks completed.\n");
    return 0;
}