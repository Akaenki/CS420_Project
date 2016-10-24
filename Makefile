SHELL=/bin/bash

CC=icc
MPI_CC=mpicc

# Flags
OPT_FLAG=-O3
OMP_FLAG=-qopenmp

# User defined values



TARGET = a.out

all : ${TARGET}

a.out: *.c
	${MPI_CC} ${OPT_FLAG} ${OMP_FLAG} -o ${TARGET}


clean:
	rm -f *.out *.o ${TARGET}

