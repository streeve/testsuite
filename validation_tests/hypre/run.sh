#!/bin/bash
. ../../setup.sh
spack load hypre

mpirun -np 8 ./ex5big
mpirun -np 8 ./ex15big



