#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include "matrix.h"

#include <mpi.h>

////generate matrix for the size n//////
matrix_t* generate_matrix(size_t n){

  matrix_t* matrix = (matrix_t*)malloc(sizeof(matrix_t));
  int size, rank;
  size_t i, j, d;
  size_t ifirst, ilast;//THE ORIGINAL ifirst and ilast
  size_t i_interval;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  //matrix->array=(double*)malloc(n*n*sizeof(double));
  matrix->Ifirst=(size_t*)malloc((2*n-5)*sizeof(size_t));
  matrix->Ilast=(size_t*)malloc((2*n-5)*sizeof(size_t));
  matrix->process = rank;
  //initialize the element of array in the boundary
  //get the Ifirst and Ilast
  for(d=0;d<n+n-5;d++){
      ifirst=(d<n-2)?d+1:n-2;
      ilast=(d<n-2)?1:d-n+4;
      i_interval=((ifirst-ilast+1)%size==0)?(size_t)((ifirst-ilast+1)/size):(size_t)floor((ifirst-ilast+1)/size)+1;
      matrix->Ifirst[d]=max((int)ilast,(int)(ifirst-rank*i_interval));
      matrix->Ilast[d]=max((int)ilast,(int)(ifirst-(rank+1)*i_interval+1));
  }
return matrix;
}

//destroy matrix free space
void destroy_matrix(matrix_t* matrix){
  free(matrix->Ifirst);
  free(matrix->Ilast);
  free(matrix);
}