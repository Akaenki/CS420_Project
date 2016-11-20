extern double array[N][N];
#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
// the function to transfer matrix element in the d+1 row and d-1 row
double  transfer_boundary(matrix_t* matrix, size_t d){
  MPI_Barrier(MPI_COMM_WORLD);//as it should be sequantial in the d index for both MPI and openmp
  double exe_time = MPI_Wtime();
  int size, rank;
  size_t i, j;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  //step one: send/recv from odd to odd+1
  if(rank%2&&rank!= size-1){//send
    if(d>=1){// exclude that d is in the first row
    i = matrix->Ilast[d-1];//deal with d-1 row
    j = (d-1) +2 -i;
    MPI_Send(&(matrix->array[i][j]),1,MPI_DOUBLE,rank+1,0,MPI_COMM_WORLD);//send the previous line(updated)
    }
    if(d<=2*N-5){// exclude that d is in the last row
    i = matrix->Ilast[d+1];//deal with d+1 row
    j = (d+1) +2 -i;
    MPI_Send(&(matrix->array[i][j]),1,MPI_DOUBLE,rank+1,1,MPI_COMM_WORLD);//send the previous line(updated)
    }
  }
  else if(rank%2==0&&rank!=0){//recv
    if(d>=1){
    i = matrix->Ifirst[d-1]-1;//deal with d-1 row need +1 to match the rank-1 index
    j = (d-1) +2 -i;
    MPI_Recv(&(matrix->array[i][j]),1,MPI_DOUBLE,rank-1,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);//send the previous line(updated)
    }
    if(d<=2*N-5){
    i = matrix->Ifirst[d+1]-1;//deal with d+1 row need +1 to match the rank-1 index
    j = (d+1) +2 -i;
    MPI_Recv(&(matrix->array[i][j]),1,MPI_DOUBLE,rank-1,1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);//send the previous line(updated)
    }
  }

  //step two: send/recv from even to even-1
  if(rank%2==0&&rank!= 0){
    if(d>=1){// exclude that d is in the first row
    i = matrix->Ifirst[d-1];//deal with d-1 row
    j = (d-1) +2 -i;
    MPI_Send(&(matrix->array[i][j]),1,MPI_DOUBLE,rank-1,0,MPI_COMM_WORLD);//send the previous line(updated)
    }
    if(d<=2*N-5){// exclude that d is in the last row
    i = matrix->Ifirst[d+1];//deal with d+1 row
    j = (d+1) +2 -i;
    MPI_Send(&(matrix->array[i][j]),1,MPI_DOUBLE,rank-1,1,MPI_COMM_WORLD);//send the previous line(updated)
    }
  }
  else if(rank%2&&rank!=size-1){
    if(d>=1){// exclude that d is in the first row
    i = matrix->Ilast[d-1]+1;//deal with d-1 row
    j = (d-1) +2 -i;
    MPI_Recv(&(matrix->array[i][j]),1,MPI_DOUBLE,rank+1,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);//send the previous line(updated)
    }
    if(d<=2*N-5){// exclude that d is in the last row
    i = matrix->Ilast[d+1]+1;//deal with d+1 row
    j = (d+1) +2 -i;
    MPI_Recv(&(matrix->array[i][j]),1,MPI_DOUBLE,rank+1,1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);//send the previous line(updated)
    }
  }


  //step three: send/recv from even to even+1
  if(rank%2==0&&rank!= size-1){
    if(d>=1){// exclude that d is in the first row
    i = matrix->Ilast[d-1];//deal with d-1 row
    j = (d-1) +2 -i;
    MPI_Send(&(matrix->array[i][j]),1,MPI_DOUBLE,rank+1,0,MPI_COMM_WORLD);//send the previous line(updated)
    }
    if(d<=2*N-5){// exclude that d is in the last row
    i = matrix->Ilast[d+1];//deal with d+1 row
    j = (d+1) +2 -i;
    MPI_Send(&(matrix->array[i][j]),1,MPI_DOUBLE,rank+1,1,MPI_COMM_WORLD);//send the previous line(updated)
    }
  }
  else if(rank%2&&rank!=0){
    if(d>=1){// exclude that d is in the first row
    i = matrix->Ifirst[d-1]-1;//deal with d-1 row
    j = (d-1) +2 -i;
    MPI_Recv(&(matrix->array[i][j]),1,MPI_DOUBLE,rank-1,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);//send the previous line(updated)
    }
    if(d<=2*N-5){// exclude that d is in the last row
    i = matrix->Ifirst[d+1]-1;//deal with d+1 row
    j = (d+1) +2 -i;
    MPI_Recv(&(matrix->array[i][j]),1,MPI_DOUBLE,rank-1,1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);//send the previous line(updated)
    }
  }

  //step four: send/recv from odd to odd-1
  if(rank%2&&rank!= 0){
    if(d>=1){// exclude that d is in the first row
    i = matrix->Ifirst[d-1];//deal with d-1 row
    j = (d-1) +2 -i;
    MPI_Send(&(matrix->array[i][j]),1,MPI_DOUBLE,rank-1,0,MPI_COMM_WORLD);//send the previous line(updated)
    }
    if(d<=2*N-5){// exclude that d is in the last row
    i = matrix->Ifirst[d+1];//deal with d+1 row
    j = (d+1) +2 -i;
    MPI_Send(&(matrix->array[i][j]),1,MPI_DOUBLE,rank-1,1,MPI_COMM_WORLD);//send the previous line(updated)
    }
  }
  else if(rank%2==0&& rank!= size-1){
    if(d>=1){// exclude that d is in the first row
    i = matrix->Ilast[d-1]+1;//deal with d-1 row
    j = (d-1) +2 -i;
    MPI_Recv(&(matrix->array[i][j]),1,MPI_DOUBLE,rank+1,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);//send the previous line(updated)
    }
    if(d<=2*N-5){// exclude that d is in the last row
    i = matrix->Ilast[d+1]+1;//deal with d+1 row
    j = (d+1) +2 -i;
    MPI_Recv(&(matrix->array[i][j]),1,MPI_DOUBLE,rank+1,1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);//send the previous line(updated)
    }
  }
  MPI_Barrier(MPI_COMM_WORLD);//as it should be sequantial in the d index for both MPI and openmp
  exe_time -= MPI_Wtime();
  return exe_time;
}

//the function to calculate element in the matrix
void calculate(matrix_t* matrix, size_t ifirst, size_t ilast, size_t d){
  size_t i;
  if (ifirst-ilast>BEGIN_LENGTH){//decide whether or not use openmpi
  #pragma omp parallel for
  for (i = ifirst; i >= ilast; i--)
  {
      int j=d+2-i;
      matrix->array[i][j]=0.25*(matrix->array[i-1][j]+matrix->array[i+1][j]+matrix->array[i][j-1]+matrix->array[i][j+1]);
  }
  }
  else
  for (i = ifirst; i >= ilast; i--)
  {
      int j=d+2-i;
      matrix->array[i][j]=0.25*(matrix->array[i-1][j]+matrix->array[i+1][j]+matrix->array[i][j-1]+matrix->array[i][j+1]);
  }
}

double combine_matrix(matrix_t* matrix){
//not use MPI VECTOR, just transfer the elements one by one to the first
//process
  MPI_Barrier(MPI_COMM_WORLD);//as it should be sequantial in the d index for both MPI and openmp
  double exe_time = MPI_Wtime();
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  size_t d, i, j, k;
  size_t ifirst, ilast;
  for(d = 0; d<2*N-5 ; d++){
    if(rank ==0 ){
      for( k=1; k<size-1;i++){
        //first transfer the positon for each d
        MPI_Recv(&(ifirst),1,MPI_UINT64_T, k,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&(ilast),1,MPI_UINT64_T, k,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for(i=ifirst;i<=ilast;i--) {
        j=d+2-i;
        MPI_Recv(&(matrix->array[i][j]),1,MPI_DOUBLE, k , 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
      }
    }
    else{
      ifirst= matrix->Ifirst[d];
      ilast= matrix->Ilast[d];
      MPI_Send(&(ifirst),1,MPI_UINT64_T, 0,0,MPI_COMM_WORLD);
      MPI_Send(&(ilast),1,MPI_UINT64_T, 0,0,MPI_COMM_WORLD);
      for(i=ifirst;i<=ilast;i--) {
      j=d+2-i;
      MPI_Send(&(matrix->array[i][j]),1,MPI_DOUBLE, 0 ,0, MPI_COMM_WORLD);
      }
    }
  }
  MPI_Barrier(MPI_COMM_WORLD);//as it should be sequantial in the d index for both MPI and openmp
  exe_time -= MPI_Wtime();
  return exe_time;
}

// the function to use MPI for Gauss-Seidel iteration
void par_mpi_gauss_seidel(int argc, char** argv)
{
  int required = MPI_THREAD_FUNNELED;
  int provided;
  //MPI_Init_thread(&argc, &argv, required, &provided);
  MPI_Init(&argc, &argv);
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  size_t i, j, d;
  size_t iter;
  size_t ifirst, ilast;
  double transfer_time = 0;
  double total_time= MPI_Wtime();
  double inner_time;
  double combine_time;
  matrix_t* matrix = generate_matrix(N);
  for (iter = 0; iter < ITERS ; iter++)
  {
    for(d=0;d<N+N-5;d++){
      ifirst=matrix->Ifirst[d];
      ilast=matrix->Ilast[d];

      inner_time=transfer_boundary(matrix, d);
      transfer_time += inner_time;
      calculate(matrix, ifirst, ilast,d);
      MPI_Barrier(MPI_COMM_WORLD);//as it should be sequantial in the d index for both MPI and openmp
      }
    MPI_Barrier(MPI_COMM_WORLD);
  }
  combine_time=combine_matrix(matrix);
  if(rank==0)
      memcpy(array, matrix->array, sizeof(array));// copy the result from MPI to the array
  MPI_Barrier(MPI_COMM_WORLD);
  total_time = MPI_Wtime()-total_time;
  MPI_Finalize();
}
