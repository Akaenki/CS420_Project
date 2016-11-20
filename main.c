#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <mpi.h>
#include "par_Gauss_Seidel.h"
#include "matrix.h"

double array[N][N];

// Used for testing.
double correct_results[N][N];

void basic_gauss_seidel();
void par_omp_gauss_seidel();
// Initialize array to zeros.
void reset_array()
{
  memset(array, 0, sizeof(array));
}

void unit_test()
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      if (abs(correct_results[i][j] - array[i][j]) > ERROR_THRESHOLD)
      {
        printf("Incorrect result.\n");
        return;
      }
    }
  }
  printf("GOOD -- Test passed.\n");
}

int main (int argc, char** argv)
{


//  if (provided != MPI_THREAD_FUNNELED) {
//        printf("Error: Requested thread support '%d', but only received '%d'\n", required, provided);
//            return 1;
//  }
  reset_array();

  printf("Running basic sequential version to save the results.\n");


  {
    basic_gauss_seidel();
  }

  memcpy(correct_results, array, sizeof(array));

  reset_array();
  #pragma omp parallel
  {
    omp_set_num_threads(NUM_THREADS);
    if (omp_get_thread_num() == 0)
      printf("Running cache-aware parallel version with %d threads.\n", omp_get_num_threads());
  }



    par_omp_gauss_seidel();

  unit_test();

    par_mpi_gauss_seidel();

  unit_test();
}
