#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void print_enter()
{
    printf("\n");
}

void matrix_product(int n, int a[n][n], int b[n][n], int c[n][n], int threads_num)
{
    int i, j, k;
    
    #pragma omp parallel for schedule(static) collapse(3) num_threads(threads_num)
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++) 
            {
                for (k = 0; k < n; k++)
                {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    int a[800][800], b[800][800], c[800][800];
    for (int i = 0; i < 800; i++)
    {
        for (int j = 0; j < 800; j++)
        {
            a[i][j] = rand() % 100;
            b[i][j] = rand() % 100;
            c[i][j] = 0;
        }
    }

    double t1 = 0;
    for (int i = 1; i <= 100; i++)
    {
        printf("Число потоков: %d\n", i);
        
        double start = omp_get_wtime();
        matrix_product(800, a, b, c, i);
        double end = omp_get_wtime();

        double t = end - start;
        if (i == 1)
        {
            t1 = t;
        }

        printf("Время выполнения: %lf\n", t);
        printf("Эффективность: %lf\n", t1 / t);
        print_enter();
    }

    int example_a[5][5] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };
    int example_b[5][5] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };
    int example_c[5][5] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    };
    matrix_product(5, example_a, example_b, example_c, 10);
    printf("[\n");
    for (int i = 0; i < 5; i++)
    {
        printf("\t[ ");
        for (int j = 0; j < 5; j++)
        {
            printf("%d, ", example_c[i][j]);
        }
        printf("]\n");
    }
    printf("]\n");
    
    return 0;
}