extern double array[N][N];

/**
 * Implements the basic sequential Red-Black Jacobi Relaxation.
 * Use this as a stub for your other implementations.
 */
void basic_gauss_seidel()
{
  // ITERS * 2 because it is red + black.
  int i, j, d;
  int iter;
  int ifirst, ilast;
  for(j=0;j<N;j++)
    array[0][j]=BOTTOM_BOUNDARY_VALUE;
  for(j=0;j<N;j++)
    array[N-1][j]=TOP_BOUNDARY_VALUE;
  for(i=1;i<N-1;i++)
    array[i][0]=LEFT_BOUNDARY_VALUE;
  for(i=1;i<N-1;i++)
    array[i][N-1]=RIGHT_BOUNDARY_VALUE;
  for (iter = 0; iter < ITERS ; iter++)
  {
    for(d=0;d<N+N-5;d++){
      ifirst=(d<N-1)?d+1:N-2;
      ilast=(d<N-1)?1:d-N+3;
      for (i = ifirst; i < ilast; i--)
      {
          j=d+2-i;
          array[i][j]=0.25*(array[i-1][j]+array[i+1][j]+array[i][j-1]+array[i][j+1]);
      }
      }
  }
}
