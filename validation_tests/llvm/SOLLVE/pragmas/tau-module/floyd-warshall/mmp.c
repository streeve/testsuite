/**
 * floyd-warshall.c: This file is part of the PolyBench/C 3.2 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#define N 512

#define DATA_TYPE double
#define DATA_PRINTF_MODIFIER "%.2lf   "

/* Array initialization. */
static
void init_array (int n, DATA_TYPE path[n][n] ){
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      path[i][j] = ((DATA_TYPE) (i+1)*(j+1)) / n;
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static
void print_array(int n, DATA_TYPE path[n][n] ){
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      fprintf (stderr, DATA_PRINTF_MODIFIER, path[i][j]);
      if ((i * n + j) % 20 == 0) fprintf (stderr, "\n");
    }
  fprintf (stderr, "\n");
}


/* Main computational kernel. The whole function will be timed,
   including the call and return. */
static
void kernel_floyd_warshall(int n, DATA_TYPE path[n][n] ){
  int i, j, k;

#pragma scop
  for (k = 0; k < n; k++)
    {
      for(i = 0; i < n; i++)
	for (j = 0; j < n; j++)
	  path[i][j] = path[i][j] < path[i][k] + path[k][j] ?
	    path[i][j] : path[i][k] + path[k][j];
    }
#pragma endscop

}


int main(int argc, char** argv)
{
  /* Retrieve problem size. */
  int n = N;

  /* Variable declaration/allocation. */
  DATA_TYPE path[n][n];

  /* Initialize array(s). */
  init_array (n, path);

  /* Start timer. */
  //  polybench_start_instruments;

  /* Run kernel. */
  kernel_floyd_warshall (n, path);

  /* Stop and print timer. */
  //  polybench_stop_instruments;
  //  polybench_print_instruments;

  /* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  //  polybench_prevent_dce(print_array(n, POLYBENCH_ARRAY(path)));
  print_array( n, path );

  /* Be clean. */
  //  POLYBENCH_FREE_ARRAY(path);

  return 0;
}
