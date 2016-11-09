extern double array[N][N];
#include <mpi.h>


// the function to transfer matrix element in the d+1 row and d-1 row
double  transfer_boundary(matrix_t* matrix, size_t d){
  MPI_Barrier(MPI_COMM_WORLD);//as it should be sequantial in the d index for both MPI and openmp
  double exe_time = MPI_Wtime();
  int size, rank;
  size_t i, j;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  //step one: send/recv from odd to odd+1
  if(rank%2&&rank!= size-1){
    i = matrix->ilast[d-1];//deal with d-1 row
    j = (d-1) +2 -i;
    MPI_Send(&(matrix->array[i][j]),1,MPI_DOUBLE,rank+1,0,MPI_COMM_WORLD);//send the previous line(updated)
    i = matrix->ilast[d+1];//deal with d+1 row
    j = (d+1) +2 -i;
    MPI_Send(&(matrix->array[i][j]),1,MPI_DOUBLE,rank+1,1,MPI_COMM_WORLD);//send the previous line(updated)
  }
  else{
    i = matrix->ifirst[d-1]+1;//deal with d-1 row
    j = (d-1) +2 -i;
    MPI_Recv(&(matrix->array[i][j]),1,MPI_DOUBLE,rank-1,1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);//send the previous line(updated)
    i = matrix->ifirst[d+1]+1;//deal with d+1 row
    j = (d+1) +2 -i;
    MPI_Recv(&(matrix->array[i][j]),1,MPI_DOUBLE,rank-1,1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);//send the previous line(updated)
  }

  //step two: send/recv from even to even-1
  if(rank%2!=0&&rank!= 0){
    i = matrix->ilast[d-1];//deal with d-1 row
    j = (d-1) +2 -i;
    MPI_Send(&(matrix->array[i][j]),1,MPI_DOUBLE,rank-1,0,MPI_COMM_WORLD);//send the previous line(updated)
    i = matrix->ilast[d+1];//deal with d+1 row
    j = (d+1) +2 -i;
    MPI_Send(&(matrix->array[i][j]),1,MPI_DOUBLE,rank-1,1,MPI_COMM_WORLD);//send the previous line(updated)
  }
  else{
    i = matrix->ifirst[d-1]+1;//deal with d-1 row
    j = (d-1) +2 -i;
    MPI_Recv(&(matrix->array[i][j]),1,MPI_DOUBLE,rank+1,1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);//send the previous line(updated)
    i = matrix->ifirst[d+1]+1;//deal with d+1 row
    j = (d+1) +2 -i;
    MPI_Recv(&(matrix->array[i][j]),1,MPI_DOUBLE,rank+1,1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);//send the previous line(updated)
  }

  //step two: send/recv from even to even+1
  if(rank%2!=0&&rank!= size-1){
    i = matrix->ilast[d-1];//deal with d-1 row
    j = (d-1) +2 -i;
    MPI_Send(&(matrix->array[i][j]),1,MPI_DOUBLE,rank+1,0,MPI_COMM_WORLD);//send the previous line(updated)
    i = matrix->ilast[d+1];//deal with d+1 row
    j = (d+1) +2 -i;
    MPI_Send(&(matrix->array[i][j]),1,MPI_DOUBLE,rank+1,1,MPI_COMM_WORLD);//send the previous line(updated)
  }
  else{
    i = matrix->ifirst[d-1]+1;//deal with d-1 row
    j = (d-1) +2 -i;
    MPI_Recv(&(matrix->array[i][j]),1,MPI_DOUBLE,rank-1,1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);//send the previous line(updated)
    i = matrix->ifirst[d+1]+1;//deal with d+1 row
    j = (d+1) +2 -i;
    MPI_Recv(&(matrix->array[i][j]),1,MPI_DOUBLE,rank-1,1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);//send the previous line(updated)
  }

  //step two: send/recv from odd to odd-1
  if(rank%2&&rank!= 0){
    i = matrix->ilast[d-1];//deal with d-1 row
    j = (d-1) +2 -i;
    MPI_Send(&(matrix->array[i][j]),1,MPI_DOUBLE,rank-1,0,MPI_COMM_WORLD);//send the previous line(updated)
    i = matrix->ilast[d+1];//deal with d+1 row
    j = (d+1) +2 -i;
    MPI_Send(&(matrix->array[i][j]),1,MPI_DOUBLE,rank-1,1,MPI_COMM_WORLD);//send the previous line(updated)
  }
  else{
    i = matrix->ifirst[d-1]+1;//deal with d-1 row
    j = (d-1) +2 -i;
    MPI_Recv(&(matrix->array[i][j]),1,MPI_DOUBLE,rank+1,1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);//send the previous line(updated)
    i = matrix->ifirst[d+1]+1;//deal with d+1 row
    j = (d+1) +2 -i;
    MPI_Recv(&(matrix->array[i][j]),1,MPI_DOUBLE,rank+1,1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);//send the previous line(updated)
  }
  MPI_Barrier(MPI_COMM_WORLD);//as it should be sequantial in the d index for both MPI and openmp
  exe_time -= MPI_Wtime();
  return exe_time;
}

//the function to calcuate element in the matrix
void calcuate(matrix_t* matrix, size_t ifirst, size_t ilast){
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

void combine_matrix(matrix_t* matrix){

}

// the function to use MPI for Gauss-Seidel iteration
void par_mpi_gauss_seidel(matrix_t* matrix)
{
  size_t i, j, d;
  size_t iter;
  size_t ifirst, ilast;
  double transfer_time = 0;
  double total_time= MPI_Wtime();
  double inner_time;
  for (iter = 0; iter < ITERS ; iter++)
  {
    for(d=0;d<N+N-5;d++){
      ifirst=matrix->Ifirst(d);
      ilast=matrix->ilast(d);

      inner_time=transfer_boundary(matrix, d);
      transfer_time + = inner_time;
      calculate(matrix, ifirst, ilast);
      MPI_Barrier(MPI_COMM_WORLD);//as it should be sequantial in the d index for both MPI and openmp
      }
    MPI_Barrier(MPI_COMM_WORLD);
  }
  combine_matrix(matrix);
  total_time = MPI_Wtime()-total_time;
}
