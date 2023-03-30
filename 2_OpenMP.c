#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    //VARIABLES

    int num_steps = 100000000;
    
    double step;
    
    int i;

    double x, pi, sum = 0.0;

    step = 1.0 / (double)num_steps;

    //TIMERS VARIABLES START

    double inicio, inicioSeq, fim, fimSeq;

    double tempTotalSeq, tempTotal;

    double speedUp, speedUpSeq;

    //SEQUENTIAL SECTION

    inicioSeq = omp_get_wtime();

    for (i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = step * sum;

    fimSeq = omp_get_wtime();

    //PARALLEL SECTION

    inicio = omp_get_wtime();

#pragma omp parallel private(x) num_threads(3)
    {
        #pragma omp for reduction(+:sum)
        for (i = 0; i < num_steps; i++)
        {
            x = (i + 0.5) * step;
            sum = sum + 4.0 / (1.0 + x * x);
        }
    }

    pi = step * sum;

    fim = omp_get_wtime();

    //CALC TIME AND SPEEDUP SECTION

    tempTotal = fim - inicio;
    tempTotalSeq = fimSeq - inicioSeq;

    speedUp = tempTotalSeq / tempTotal;

    printf("Tempo total sequencial: %.2f \n", tempTotalSeq);
    printf("Tempo total paralelo: %.2f \n", tempTotal);

    printf("SpeedUp: %.2f \n", speedUp);

    return 0;
}