#include<stdlib.h>
#include<stdio.h>
#include "matrix.h"

#include <mpi.h>

////generate matrix for the size n//////
matrix* generate_matrix(size_t n){

  matrix_t matrix = (matrix_t*)malloc(sizeof(matrix_t));
  int size, rank;
  size_t i, j, d;
  size_t ifirst, ilast;//THE ORIGINAL ifirst and ilast
  size_t i_interval;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  matrix->array=malloc(n*n*sizeof(double));
  matrix->Ifirst=malloc((2*n-5)sizeof(double));
  matrix->Ilast=malloc((2*n-5)sizeof(double));
  matrix->process = rank;
  //initialize the element of array in the boundary
  for(j=0;j<N;j++)
    matrix->array[0][j]=BOTTOM_BOUNDARY_VALUE;
  for(j=0;j<N;j++)
    matrix->array[N-1][j]=TOP_BOUNDARY_VALUE;
  for(i=1;i<N-1;i++)
    matrix->array[i][0]=LEFT_BOUNDARY_VALUE;
  for(i=1;i<N-1;i++)
    matrix->array[i][N-1]=RIGHT_BOUNDARY_VALUE;

  //get the Ifirst and Ilast
  for(d=0;d<N+N-5;d++){
      ifirst=(d<N-2)?d+1:N-2;
      ilast=(d<N-2)?1:d-N+4;
      i_interval=(size_t)floor((ifirst-ilast+1)/size);
      matrix->Ifirst(d)=max(ilast,ifirst-rank*i_interval);
      matrix->Ilast(d)=max(ilast,ifirst-(rank+1)*i_interval+1);
      }
}

//destroy matrix free space
void destroy_matrix(matrix_t* matrix){
  free(matrix->array);
  free(matrix->Ifirst);
  free(matrix->Ilast);
  free(matrix);
}
