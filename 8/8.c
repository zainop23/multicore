#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1000000

int array[SIZE];

int main() {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 100;
    }

    int sequential_sum = 0;
    double start = omp_get_wtime();

    for (int i = 0; i < SIZE; i++) {
        sequential_sum += array[i];
    }

    double end = omp_get_wtime();

    printf("Sequential Sum: %d\n", sequential_sum);
    printf("Sequential Time: %f seconds\n", end - start);

    int parallel_sum = 0;
    start = omp_get_wtime();

    #pragma omp parallel for reduction(+:parallel_sum)
    for (int i = 0; i < SIZE; i++) {
        parallel_sum += array[i];
    }

    end = omp_get_wtime();

    printf("Parallel Sum: %d\n", parallel_sum);
    printf("Parallel Time: %f seconds\n", end - start);

    if (sequential_sum == parallel_sum) {
        printf("Both sums are equal.\n");
    } else {
        printf("Results are different!\n");
    }

    return 0;
}