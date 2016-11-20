SHELL=/bin/bash

CC=mpiicc

# The array size.
#N= 5 
N= 26

# The length where to use the openmpi
BEGIN_LENGTH_OMP= 1000
# How many iterations to run
ITERS=20

# Boundary values.
TOP_BOUNDARY_VALUE=5.8
BOTTOM_BOUNDARY_VALUE=10.2
LEFT_BOUNDARY_VALUE=4.3
RIGHT_BOUNDARY_VALUE=9.2

# Number of threads.
NUM_THREADS_TAUB=12

# Compiler optimization level.
OPT_LEVEL=-O0 #-qopt-report


##########################################
# DO NOT MODIFY ANYTHING BELOW THIS LINE #
# DO NOT MODIFY ANYTHING BELOW THIS LINE #
# DO NOT MODIFY ANYTHING BELOW THIS LINE #
# DO NOT MODIFY ANYTHING BELOW THIS LINE #
##########################################

# Used for checking the results.
ERROR_THRESHOLD=1e-3

# The papi library location.
PAPI_LIB_DIR=/opt/cray/papi/5.4.3.1/lib
PAPI_INC_DIR=/opt/cray/papi/5.4.3.1/include

# Common program arguments.
COMMON_PROG_ARGS=-DN=$(N) \
			 		  		 -DITERS=$(ITERS) \
			        	 -DTOP_BOUNDARY_VALUE=$(TOP_BOUNDARY_VALUE) \
			        	 -DBOTTOM_BOUNDARY_VALUE=$(BOTTOM_BOUNDARY_VALUE) \
			        	 -DLEFT_BOUNDARY_VALUE=$(LEFT_BOUNDARY_VALUE) \
			        	 -DRIGHT_BOUNDARY_VALUE=$(RIGHT_BOUNDARY_VALUE) \
			        	 -DERROR_THRESHOLD=$(ERROR_THRESHOLD) \
								 -std=c99 \
								 -qopenmp

# Program arguments for Taub.
TAUB_PROG_ARGS=$(COMMON_PROG_ARGS) \
  			     	 -DNUM_THREADS=$(NUM_THREADS_TAUB) \
  			     	 -DBEGIN_LENGTH=$(BEGIN_LENGTH_OMP) \

# Compilation command for Taub, no PAPI.
TAUB_NOPAPI_CC=$(CC) -DNOPAPI $(TAUB_PROG_ARGS)

all: taub_no_papi

taub_no_papi: *.c
	$(TAUB_NOPAPI_CC) *.c -o taub_no_papi

clean:
	rm -f taub_no_papi
