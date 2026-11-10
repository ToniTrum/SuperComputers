#include <stdio.h>
#include <omp.h>


int main(int argc, char *argv[])
{
    int n = 20;
    int a[n], result[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = 2 << i;
    }

    omp_lock_t lock;
    omp_init_lock(&lock);

    int index = n - 1;
    #pragma omp parallel
    {
        while (1) 
        {
            int thread_index;
            
            omp_set_lock(&lock);

            if (index < 0)
            {
                omp_unset_lock(&lock);
                break;
            }
            thread_index = index;
            index--;

            omp_unset_lock(&lock);

            if (thread_index > 0)
            {
                result[n - thread_index - 1] = a[thread_index] - a[thread_index - 1];
            }
            else
            {
                result[n - 1] = a[0]; 
            }
        }
    }

    omp_destroy_lock(&lock);

    printf("result = [ ");
    for (int i = 0; i < n; i++) 
    {
        printf("%d, ", result[i]);
    }
    printf("]\n");

    return 0;
}