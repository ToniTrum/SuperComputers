#include <stdio.h>
#include <omp.h>

void print_enter() {
    printf("\n");
}


int main(int argc, char *argv[]) 
{
    /* Задание 1 */
    #ifdef _OPENMP
    printf("OpenMP is supported!\n");
    #endif
    print_enter();

    /* Задание 2 */
    printf("Последовательная область 1\n");
    #pragma omp parallel
    {
        printf("Параллельная область\n");
    }
    printf("Последовательная область 2\n");
    print_enter();

    #pragma omp parallel num_threads(10)
    {
        int num = omp_get_thread_num();
        
        #pragma omp master
        {
            printf("Всего потоков: %d\n", omp_get_num_threads());
        }
        
        printf("Номер потока: %d\n", num);
    }
    print_enter();

    /* Задание 3 */
    omp_set_num_threads(2);

    printf("== Область 1 ==\n");
    #pragma omp parallel num_threads(10)
    {
        int num = omp_get_thread_num();
        
        #pragma omp master
        {
            printf("Всего потоков: %d\n", omp_get_num_threads());
        }
        
        printf("Номер потока: %d\n", num);
    }

    printf("== Область 2 ==\n");
    #pragma omp parallel
    {
        int num = omp_get_thread_num();
        
        #pragma omp master
        {
            printf("Всего потоков: %d\n", omp_get_num_threads());
        }
        
        printf("Номер потока: %d\n", num);
    }
    
    return 0;
}