#include <stdio.h>
#include <pthread.h>
int arr[8] = {1, 2, 3, 4, 5, 6, 7, 8};
int sum[2] = {0, 0};
void *add(void *arg)
{
    long id = (long)arg;
    for (int i = id * 4; i < (id + 1) * 4; i++)
        sum[id] += arr[i];
    return NULL;
}

int main()
{
    pthread_t t[2];
    for (long i = 0; i < 2; i++)
        pthread_create(&t[i], NULL, add, (void *)i);
    for (int i = 0; i < 2; i++)
        pthread_join(t[i], NULL);
    printf("Total Sum: %d\n", sum[0] + sum[1]);
    return 0;
}