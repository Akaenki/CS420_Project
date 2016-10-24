#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include "papi_support.h"

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
  papi_init();

  reset_array();

  printf("Running basic sequential version to save the results.\n");

  /**
   * THIS IS WHERE YOU CHOOSE WHICH COUNTERS TO RUN.
   * ONLY ADD AT MOST 2 COUNTERS PER RUN.
   *
   * The current example adds L2 Accesses and L2 Misses.
   */

#ifndef NOPAPI //papi_prepare_counter(PAPI_L2_DCM);
  //papi_prepare_counter(PAPI_L2_DCA);
  papi_prepare_counter(PAPI_L3_LDM);
  papi_prepare_counter(PAPI_L3_TCM);
#endif

  /** ============================================== */

  papi_start();
  {
    basic_gauss_seidel();
  }
  papi_stop_and_report();

  memcpy(correct_results, array, sizeof(array));

  // Run cache-aware sequential code.
  reset_array();
  #pragma omp parallel
  {
    if (omp_get_thread_num() == 0)
      printf("Running cache-aware parallel version with %d threads.\n", omp_get_num_threads());
  }
  papi_start();
  {
    par_omp_gauss_seidel();
  }
  papi_stop_and_report();

  unit_test();

}
