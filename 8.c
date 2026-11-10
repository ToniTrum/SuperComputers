#include <iso646.h>
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 256

static char current_task[BUF_SIZE];
static int task_ready = 0;
static int result_ready = 1;
static omp_lock_t lock;


void client(const char *task[])
{
    for (int i = 0; task[i] != NULL; i++)
    {
        int ok = 0;
        while (!ok) 
        {
            omp_set_lock(&lock);
            if (result_ready) 
            {
                ok = 1;
                result_ready = 0;
            }
            omp_unset_lock(&lock);
        }

        strncpy(current_task, task[i], BUF_SIZE - 1);
        current_task[BUF_SIZE - 1] = '\0';

        omp_set_lock(&lock);
        task_ready = 1;
        omp_unset_lock(&lock);
    }

    int ok = 0;
    while (!ok)
    {
        omp_set_lock(&lock);
        if (result_ready) 
        {
           ok = 1; 
           result_ready = 0;
        }
        omp_unset_lock(&lock);
    }
    
    strncpy(current_task, "end", BUF_SIZE - 1);
    current_task[BUF_SIZE - 1] = '\0';
    
    omp_set_lock(&lock);
    task_ready = 1;
    omp_unset_lock(&lock);
}

double server()
{
    double res = 0;

    while (1) 
    {
        int ok = 0;
        while (!ok) 
        {
            omp_set_lock(&lock);
            if (task_ready) 
            {
                ok = 1;
                task_ready = 0;
            }
            omp_unset_lock(&lock);
        }
        
        char query[BUF_SIZE];
        strncpy(query, current_task, BUF_SIZE - 1);
        query[BUF_SIZE - 1] = '\0';

        if (strcmp(query, "end") == 0)
        {
            break;
        }
        
        char param_1[64], param_2[64], operation;
        sscanf(query, "%63s %c %63s", param_1, &operation, param_2);
        
        double value_1 = (strcmp(param_1, "res") == 0) ? res : strtod(param_1, NULL);
        double value_2 = (strcmp(param_2, "res") == 0) ? res : strtod(param_2, NULL);

        switch (operation) 
        {
            case '+':
                res = value_1 + value_2;
                break;
            case '-':
                res = value_1 - value_2;
                break;
            case '*':
                res = value_1 * value_2;
                break;
            case '/':
                res = value_1 / value_2;
                break;
        }

        omp_set_lock(&lock);
        result_ready = 1;
        omp_unset_lock(&lock);
    }

    return res;
}

int main(int argc, char *argv[])
{
    const char *task[] = {
        "5 + 3", 
        "res / 2", 
        "24 / res", 
        "res * res", 
        "res - 6", 
        NULL
    }; 
    double res;
    omp_init_lock(&lock);
    
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                client(task);
            }
            #pragma omp section
            {
                res = server();
            }
        }
    }

    omp_destroy_lock(&lock);
    printf("res=%lf\n", res);

    return 0;
}