#include <stdlib.h>
#include <time.h>
#include "MatlabHelper.h"

/* This function provides the actual Matlab interface. */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  struct sparsematrix *matrix;

  /* converting from Matlab to Mondriaan */
  matrix = ConvertMatlabToMondriaan(prhs[0]);
  plhs[0] = ConvertMondriaanToMatlab(matrix);

  MMDeleteSparseMatrix(matrix);
}
