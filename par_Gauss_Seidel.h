#include "matrix.h"
void par_omp_gauss_seidel();
double  transfer_boundary(matrix_t* matrix, size_t d);
void calculate(matrix_t* matrix, size_t ifirst, size_t ilast);
double combine_matrix(matrix_t* matrix);
void par_mpi_gauss_seidel();
