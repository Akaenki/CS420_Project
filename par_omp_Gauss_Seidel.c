extern double array[N][N];
#include <omp.h>
#include <stdio.h>

/**
 * Implements the basic sequential Red-Black Jacobi Relaxation.
 * Use this as a stub for your other implementations.
 */
void par_omp_gauss_seidel(){
    for(int iter = 0; iter < ITERS; iter++){
        for(int d = 0; d < N+N-1; d++){ //total # of diagonals: 2N-2
            int ifirst = (d < N) ? d : N-1;
            int ilast  = (d < N) ? 0 : d-N+1;
            
            if((ifirst-ilast) >= BEGIN_LENGTH){ //parallel
#pragma omp parallel for schedule(dynamic)
                for(int i = ifirst; i >= ilast; i--){ //from left to right
                    int j = d - i;
                    
                    double top, bottom, left, right;
                    
                    if(i == 0) top = TOP_BOUNDARY_VALUE;
                    else top  = array[i-1][j];
                    if(i == N-1) bottom = BOTTOM_BOUNDARY_VALUE;
                    else bottom = array[i+1][j];
                    if(j = 0) left = LEFT_BOUNDARY_VALUE;
                    else left = array[i][j-1];
                    if(j = N-1) right = RIGHT_BOUNDARY_VALUE;
                    else right = array[i][j+1];
                    
                    array[i][j] = 0.25*(top + bottom + left + right);
                }
            } else{ //do not parallel
                for(int i = ifirst; i >= ilast; i--){
                    int j = d - i;
                    
                    double top, bottom, left, right;
                    
                    if(i == 0) top = TOP_BOUNDARY_VALUE;
                    else top  = array[i-1][j];
                    if(i == N-1) bottom = BOTTOM_BOUNDARY_VALUE;
                    else bottom = array[i+1][j];
                    if(j = 0) left = LEFT_BOUNDARY_VALUE;
                    else left = array[i][j-1];
                    if(j = N-1) right = RIGHT_BOUNDARY_VALUE;
                    else right = array[i][j+1];
                    
                    array[i][j] = 0.25*(top + bottom + left + right);
                }
            }
        }
    }
}

