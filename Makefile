SHELL=/bin/bash

CC=icc

# The array size.
N= 5000

# How many iterations to run
ITERS=100

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
ERROR_THRESHOLD=1e-4

# The papi library location.
PAPI_LIB_DIR=/usr/local/apps/papi/5.4.1/lib
PAPI_INC_DIR=/usr/local/apps/papi/5.4.1/include

# Common program arguments.
COMMON_PROG_ARGS=-DN=$(N) \
			 		  		 -DITERS=$(ITERS) \
			        	 -DTOP_BOUNDARY_VALUE=$(TOP_BOUNDARY_VALUE) \
			        	 -DBOTTOM_BOUNDARY_VALUE=$(BOTTOM_BOUNDARY_VALUE) \
			        	 -DLEFT_BOUNDARY_VALUE=$(LEFT_BOUNDARY_VALUE) \
			        	 -DRIGHT_BOUNDARY_VALUE=$(RIGHT_BOUNDARY_VALUE) \
			        	 -DERROR_THRESHOLD=$(ERROR_THRESHOLD) \
								 -std=c99 \
								 -qopenmp \
								 $(OPT_LEVEL)

# Program arguments for Taub.
TAUB_PROG_ARGS=$(COMMON_PROG_ARGS) \
  			     	 -DNUM_THREADS=$(NUM_THREADS_TAUB) \

# Compilation command for Taub, no PAPI.
TAUB_NOPAPI_CC=$(CC) -DNOPAPI $(TAUB_PROG_ARGS)

TAUB_PAPI_CC=$(CC) -I${PAPI_INC_DIR} -L$(PAPI_LIB_DIR) -lpapi $(TAUB_PROG_ARGS)

all: taub_no_papi taub_with_papi

taub_no_papi: *.c
	$(TAUB_NOPAPI_CC) *.c -o taub_no_papi

taub_with_papi: *.c
	$(TAUB_PAPI_CC) *.c -o taub_with_papi

clean:
	rm -f *.out *.o *.optrpt taub_no_papi taub_with_papi
