#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "MatlabHelper.h"

/* This function provides the actual Matlab interface. */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  FILE* File;
  struct sparsematrix matrix;
  File = fopen("../../matrices/m_testbed/tbdlinux.mtx", "r");
  if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
  fclose(File);

  plhs[0] = ConvertMondriaanToMatlab(&matrix);
  MMDeleteSparseMatrix(&matrix);
}
