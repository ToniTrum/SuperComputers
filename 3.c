#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void print_enter()
{
    printf("\n");
}

void search_min_max(int a[], int n, int threads_num)
{
    int global_min = RAND_MAX;
    int global_max = -1;
    
    #pragma omp parallel num_threads(threads_num) reduction(min: global_min) reduction(max: global_max)
    {
        #pragma omp for
            for (int i = 0; i < n; i++)
            {
                if (a[i] < global_min)
                {
                    global_min = a[i];
                }
                if (a[i] > global_max) 
                {
                    global_max = a[i];
                }
            }
    }

    printf("min=%d\n", global_min);
    printf("max=%d\n", global_max);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    int a[1000000];
    for (int i = 0; i < 1000000; i++)
    {
        a[i] = rand();
    }

    for (int i = 1; i <= 10; i++)
    {
        printf("Число потоков: %d\n", i);
        
        double start = omp_get_wtime();
        search_min_max(a, 1000000, i);
        double end = omp_get_wtime();

        printf("Время выполнения: %lf\n", end - start);
        print_enter();
    }

    int example[] = {1, 0, 10, 5, 123, 2345, 3, 43, 67, 324};
    search_min_max(example, 10, 10);
    
    return 0;
}