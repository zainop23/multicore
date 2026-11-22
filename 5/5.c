#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int arr[SIZE], temp[SIZE];

void merge(int l, int mid, int r) {
    int i = l, j = mid + 1, k = l;

    while (i <= mid && j <= r) {
        temp[k++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];
    }
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= r) {
        temp[k++] = arr[j++];
    }
    for (i = l; i <= r; i++) {
        arr[i] = temp[i];
    }
}

void merge_sort(int l, int r) {
    if (l < r) {
        int mid = (l + r) / 2;
        merge_sort(l, mid);
        merge_sort(mid + 1, r);
        merge(l, mid, r);
    }
}

void *runner(void *arg) {
    long id = (long)arg;
    int start = id * (SIZE / 4);
    int end = start + (SIZE / 4) - 1;

    merge_sort(start, end);
    return NULL;
}

int main() {
    pthread_t t[4];

    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000;
    }

    for (long i = 0; i < 4; i++) {
        pthread_create(&t[i], NULL, runner, (void *)i);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(t[i], NULL);
    }

    merge(0, (SIZE / 4) - 1, (SIZE / 2) - 1);
    merge(SIZE / 2, (3 * SIZE / 4) - 1, SIZE - 1);
    merge(0, (SIZE / 2) - 1, SIZE - 1);

    printf("Sorted Array:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}