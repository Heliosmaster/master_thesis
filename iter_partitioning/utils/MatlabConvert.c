#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "MatlabHelper.h"

/* This function provides the actual Matlab interface. */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  struct sparsematrix *matrix;

  /* converting from Matlab to Mondriaan */
  matrix = ConvertMatlabToMondriaan(prhs[0]);
  mxArray* matrix2 = ConvertMondriaanToMatlab(matrix);
/*  int i;

  for(i=0;i<1;i++){
	  matrix = ConvertMatlabToMondriaan(matrix2);
	  matrix2 = ConvertMondriaanToMatlab(matrix);
  }*/
 
  /* converting back from Mondriaan to Matlab */
  plhs[0] =  matrix2; 
  MMDeleteSparseMatrix(matrix);
}
