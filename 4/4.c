#include <pthread.h>
#include <stdio.h>

int bal = 1000;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *trans(void *arg) {
    long amt = (long)arg;

    pthread_mutex_lock(&lock);
    if (bal + amt >= 0) {
        bal += amt;
        printf("Success: %ld | Bal: %d\n", amt, bal);
    } else {
        printf("Denied: %ld\n", amt);
    }

    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t t[5];
    int amts[5] = {-200, 100, -300, 150, -400};

    for (long i = 0; i < 5; i++) {
        pthread_create(&t[i], NULL, trans, (void *)(long)amts[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(t[i], NULL);
    }

    printf("Final Balance: %d\n", bal);
    return 0;
}