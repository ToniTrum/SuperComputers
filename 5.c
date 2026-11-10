#include <stdio.h>
#include <omp.h>
#include <math.h>

void print_enter()
{
    printf("\n");
}

int main(int argc, char *argv[])
{
    long long N;
    scanf("%lld", &N);
    
    double start = omp_get_wtime();

    double pi = 0;
    #pragma omp parallel reduction(+: pi)
    {
        #pragma omp for
            for (long long i = 0; i < N; i++)
            {
                double x_i = (i + 0.5) / N;
                pi += 4.0 / (1.0 + x_i * x_i);
            }
    }
    pi /= N;
    
    double end = omp_get_wtime();

    printf("П=%.20f\n", pi);
    printf("Точность: %.20f\n", fabs(pi - M_PI));
    printf("Время выполнения: %lf\n", end - start);
    print_enter();
    
    return 0;
}