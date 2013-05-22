#include <stdlib.h>
#include <time.h>
#include "createB.c"
#include "utils.h"
#include "MatlabHelper.h"

/* This function provides the actual Matlab interface. */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  struct sparsematrix *Ac, *Ar;

  /* converting from Matlab to Mondriaan */
  Ac = ConvertMatlabToMondriaan(prhs[0]);
  Ar = ConvertMatlabToMondriaan(prhs[1]);
 
  struct sparsematrix B = createB(Ac,Ar); 

  /* converting back from Mondriaan to Matlab */
  plhs[0] = ConvertMondriaanToMatlab(&B);
  
  MMDeleteSparseMatrix(Ac);
  MMDeleteSparseMatrix(Ar);
}
