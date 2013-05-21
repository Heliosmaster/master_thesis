#include <stdlib.h>
#include <time.h>
#include "localview.h"
#include "../utils/utils.h"
#include "../utils/MatlabHelper.h"

/* This function provides the actual Matlab interface. */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  struct sparsematrix *MondriaanMatrix;

  /* converting from Matlab to Mondriaan */
  MondriaanMatrix = ConvertMatlabToMondriaan(prhs[0]);
  
  /* performing split */
  struct twomatrices lw = localview(MondriaanMatrix);

  /* separating the two parts */
  struct sparsematrix matrix = lw.Ac;
  struct sparsematrix matrix2 = lw.Ar;
  
  /* converting back from Mondriaan to Matlab */
  plhs[0] = ConvertMondriaanToMatlab(&matrix);
  plhs[1] = ConvertMondriaanToMatlab(&matrix2);
  
  MMDeleteSparseMatrix(MondriaanMatrix);
}

