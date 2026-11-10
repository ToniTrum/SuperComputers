#include <stdio.h>
#include <omp.h>

void print_enter()
{
    printf("\n");
}

int main(int argc, char *argv[])
{
    /* Задание 1 */
    int count = 0;
    #pragma omp parallel reduction(+: count)
    {
        count++;
        printf("Занчение count: %d\n", count);
    }
    printf("Число потоков: %d\n", count);
    print_enter();

    int A[10], B[10], C[10], i, n;
    for (i = 0; i < 10; i++)
    {
        A[i] = i; B[i] = 2 * i; C[i] = 0;
    }
    #pragma omp parallel shared(A, B, C) private(i, n)
    {
        n = omp_get_thread_num();
        #pragma omp for
            for (i = 0; i < 10; i++)
            {
                C[i] = B[i] + A[i];
                printf("Поток %d сложила элементы с номером %d\n", n, i);
            }
    }
    print_enter();

    int a[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    
    int sum = 0;
    #pragma omp parallel shared(a) private(i)
    {
        #pragma omp for
            for (i = 0; i < 10; i++)
            {
                sum += a[i];
            }
    }
    printf("Занчение sum: %d\n", sum);
    sum = 0;
    #pragma omp parallel shared(a) private(i) reduction(+: sum)
    {
        #pragma omp for
            for (i = 0; i < 10; i++)
            {
                sum += a[i];
            }
    }
    printf("Занчение sum: %d\n", sum);
    print_enter();

    /* Задание 2 */
    sum = 0; 
    #pragma omp parallel 
    { 
        int local_sum = 0; 
        #pragma omp for 
            for (i = 0; i < 10; ++i) 
                local_sum += a[i]; 
        #pragma omp atomic 
            sum += local_sum; 
    } 
    printf("sum=%d\n", sum);
    print_enter();

    /* Задание 3 */
    sum = 0; 
    #pragma omp parallel 
    { 
        int local_sum = 0; 
        #pragma omp for 
            for (i = 0; i < 10; ++i) 
                local_sum += a[i]; 
        #pragma omp critical
        {
            sum += local_sum; 
        }
    } 
    printf("sum=%d\n", sum);
    
    return 0;
}