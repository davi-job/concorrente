#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000

int main(int argc, char **argv)
{

    // MPI INIT

    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //CODE

    time_t t;
    srand(time(NULL));

    int vetor[MAX];

    if(rank == 0){

        int sum1, sum2;

        for (int i = 0; i < MAX; i++)
        {
            int num = rand() % MAX + 1;
            vetor[i] = num;
        }

        MPI_Bcast(vetor, MAX, MPI_INT, 0, MPI_COMM_WORLD);

        MPI_Recv(&sum1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&sum2, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Soma do rank 1: %d \n", sum1);
        printf("Soma do rank 2: %d \n\n", sum2);
    }

    else if(rank == 1){

        MPI_Bcast(vetor, MAX, MPI_INT, 0, MPI_COMM_WORLD);

        int sumi1 = 0;

        for (int i = 0; i < MAX; i++){
            sumi1 += vetor[i];
        }

        MPI_Send(&sumi1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    else if(rank == 2){

        MPI_Bcast(vetor, MAX, MPI_INT, 0, MPI_COMM_WORLD);

        int sumi2 = 0;
        
        for (int i = 0; i < MAX; i++)
        {
            sumi2 += vetor[i] * 2;
        }

        MPI_Send(&sumi2, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // MPI CLOSURE

    MPI_Finalize();
}

