#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void print_enter()
{
    printf("\n");
}

void scalar_product(int a[], int b[], int n, int threads_num)
{
    int i;
    int result = 0;
    
    #pragma omp parallel num_threads(threads_num) reduction(+: result)
    {
        #pragma omp for
            for (i = 0; i < n; i++)
            {
                result += a[i] * b[i];
            }
    }

    printf("res=%d\n", result);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    int a[1000000], b[1000000];
    for (int i = 0; i < 1000000; i++)
    {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    for (int i = 1; i <= 10; i++)
    {
        printf("Число потоков: %d\n", i);
        
        double start = omp_get_wtime();
        scalar_product(a, b, 1000000, i);
        double end = omp_get_wtime();

        printf("Время выполнения: %lf\n", end - start);
        print_enter();
    }

    int example_a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int example_b[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    scalar_product(example_a, example_b, 10, 10);
    
    return 0;
}