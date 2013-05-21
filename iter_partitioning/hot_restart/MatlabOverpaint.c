#include <stdlib.h>
#include <time.h>
#include "overpaint.h"
#include "../utils/utils.h"
#include "../utils/MatlabHelper.h"

/* This function provides the actual Matlab interface. */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  struct sparsematrix* MondriaanMatrix;
  int i;

  /* converting the matrix from Matlab to Mondriaan */
  MondriaanMatrix = ConvertMatlabToMondriaan(prhs[0]);

  /* computing the length of the priority vector */
  int length = MondriaanMatrix->m+MondriaanMatrix->n;

  /* getting the vector as double*, DO NOT FREE (the memory is allocated in Matlab!) */
  double* inputVec = mxGetPr(prhs[1]);

  /* switching from mondriaan numbering of rows/cols to C */
  for(i=0;i<length;i++) inputVec[i] -= 1.0;

  /* explicit conversion of double* to long* */
  long* vec = double_array_to_long(inputVec,length);
  
  /* switching from Matlab matrix storage (ascending columns) to ascending rows */
  struct sparsematrixplus matplus = reorder_row_incr(MondriaanMatrix);
  struct sparsematrix mat = matplus.matrix;
  
  /* performing split */
  struct twomatrices two = overpaint(&mat,vec);

  /* separating the two parts */
  struct sparsematrix matrix = two.Ac;
  struct sparsematrix matrix2 = two.Ar;
  
  /* converting back from Mondriaan to Matlab */  
  plhs[0] = ConvertMondriaanToMatlab(&matrix);
  plhs[1] = ConvertMondriaanToMatlab(&matrix2);
  
  vecfreel(vec);
  MMDeleteSparseMatrix(&mat);
  MMDeleteSparseMatrix(&two.Ar);
  MMDeleteSparseMatrix(&two.Ac);
  vecfreel(matplus.perm);
  MMDeleteSparseMatrix(MondriaanMatrix);
}

