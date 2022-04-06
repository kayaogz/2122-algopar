#include <cstdio>
#include "mpi.h"
#include <unistd.h>

int calcul2()
{
  sleep(2);
  return 2;
}

int calcul3()
{
  sleep(3);
  return 3;
}

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0) {
    int deux = calcul2();
    printf("deux = %d\n", deux);
    int trois;
    MPI_Recv(&trois, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    int cinq = deux + trois;
    printf("cinq = %d\n", cinq);
    MPI_Send(&cinq, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
  } else if (rank == 1) {
    int trois = calcul3();
    printf("trois = %d\n", trois);
    MPI_Send(&trois, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    int cinq;
    MPI_Recv(&cinq, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("cinq = %d\n", cinq);
  }

  MPI_Finalize();
  return 0;
}
