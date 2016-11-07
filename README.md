#CS420 project: Paralleled Gauss-Seidel Method
Group Member: [Fangxiaozhi Yu](https://github.com/fyu10), [Linling Miao](https://github.com/Akaenki), [Guanfeng Gao](https://github.com/ggao5)

#Objectives
The goal of this project is to develop an algorithm to parallel the [Gauss-Seidel Method](https://en.wikipedia.org/wiki/Gauss%E2%80%93Seidel_method) using OpenMP and Open-MPI to achieve th best perfomane.
The performance is tested by runinng the iterative method for a fixed number of iterations and collect the average execution time. 

TODO: 
1. Change the size of the matri from NN to MxN
2. May need a load balancing function?


#Changes
* The boundary values are no longer in the allocated matrix (treat the boundary values as environmental variables)
