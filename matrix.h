#pragma once 
#define min(a,b) a<b ? a:b
#define max(a,b) a>b ? a:b

typedef struct{
  double array[N][N];
  size_t* Ifirst;//array of the ifirst, which have 2n-5 element
  size_t* Ilast;//array of the ilast, which have 2n-5 element
  size_t n;//total size of the array
  size_t process;
} matrix_t;

matrix_t* generate_matrix(size_t n);

void destroy_matrix(matrix_t* matrix);
