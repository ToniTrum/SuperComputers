#include <stdio.h>
#include <omp.h>


int main(int argc, char *argv[]) 
{
    omp_set_num_threads(2);

    printf("== Область 1 ==\n");
    #pragma omp parallel num_threads(10)
    {
        int num = omp_get_thread_num();
        if (num == 0)
        {
            printf("Всего потоков: %d\n", omp_get_num_threads());
        }
        
        printf("Номер потока: %d\n", num);
    }

    printf("== Область 2 ==\n");
    #pragma omp parallel
    {
        int num = omp_get_thread_num();
        if (num == 0)
        {
            printf("Всего потоков: %d\n", omp_get_num_threads());
        }
        
        printf("Номер потока: %d\n", num);
    }

    return 0;
}