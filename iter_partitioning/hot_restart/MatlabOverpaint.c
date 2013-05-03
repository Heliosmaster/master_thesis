#include <stdlib.h>
#include <time.h>
#include "overpainting.c"

/* Matlab include files. */
#include "mex.h"
#include "matrix.h"

/* For compatibility with older versions of Matlab, we need to define mwSize and mwIndex ourselves. */
#ifndef mwSize
#define mwSize size_t
#endif
#ifndef mwIndex
#define mwIndex size_t
#endif

/*
Let us take a look at the Matlab sparse matrix format (see mxSetJc in the Matlab help).
Denote the row indices by RI, column indices by CI, and data by D.
Then the RI array contains the indices of the rows that contain non-zero elements offset by 1, so if RI[0] = 0, then the first row of the matrix contains a non-zero element.
The D array contains the values of the non-zero entries.
Finally the CI array is the most complicated: CI[i] is the index in RI and D of the first non-zero entry in the i-th column.

So if we would have the 16x5 matrix A with non-zero entries A(2, 2) = 9, A(4, 2) = 7, A(13, 5) = 2, then
RI = 2 4 13
D = 9 7 2
CI = 0 0 2 2 2 3 (no elements in first column, two elements in second column, no elements in third and fourth column, one if fifth column).

Note that this corresponds to the CCS format.
*/

/* This structure hold the partitioning statistics. */
struct MondriaanStats {
  /* Maximum and minimum number of nonzeros assigned to a single processor. */
  long MaxNz, MinNz;
  double Epsilon;
  long MaxComU, MaxComV;
  long ComVolU, ComVolV;
  double Duration;
};

/* This structure will be used to translate a Mondriaan sparse matrix back to the Matlab format. */
struct MondriaanTriplet {
  long Row, Column;
  double ReValue, ImValue;
};

int MaxIterations = -1;

/* This callback ensures that we stop after MaxIterations iterations. */
int Callback(int Iteration, int SplitPart, const struct sparsematrix *A) {
  if (MaxIterations <= 0) return true;
  
  return (Iteration < MaxIterations);
}


/* This function converts a Matlab sparse matrix to a Mondriaan sparse matrix. */
struct sparsematrix *ConvertMatlabToMondriaan(const mxArray *A) {
  struct sparsematrix *B;
  mwIndex *AIr, *AJc;
  double *APr, *APi;
  long i, j, k;
  
  /* Read input Matlab matrix data. */
  if (A == NULL) mexErrMsgTxt ("Null variable pointer!");
  if (mxGetNumberOfDimensions (A) != 2 || !mxIsSparse (A) || mxGetM (A) <= 1 || mxGetN (A) <= 1) mexErrMsgTxt ("Matrix that we have to retrieve is not a sparse matrix!");
  
  APr = mxGetPr(A);
  APi = (mxIsComplex(A) ? mxGetPi(A) : NULL);
  AIr = mxGetIr(A);
  AJc = mxGetJc(A);
  
  if (!APr || !AIr || !AJc) mexErrMsgTxt ("Matrix data could not be retrieved!");
  
  B = (struct sparsematrix *)malloc(sizeof (struct sparsematrix));
  
  if (B == NULL) mexErrMsgTxt("Could not allocate Mondriaan matrix!");
  
  /* First initialise the sparse matrix to its default parameters. */
  if (!MMSparseMatrixInit(B)) mexErrMsgTxt("Unable to initialise matrix!");
  
  /* Now fill in the parameters from A. */
  B->MMTypeCode[0] = 'M';
  B->MMTypeCode[1] = 'C';
  B->MMTypeCode[2] = (APi != NULL ? 'C' : 'R');
  B->MMTypeCode[3] = 'G';
  
  B->m = mxGetM(A);
  B->n = mxGetN(A);
  B->NrNzElts = AJc[B->n];
  
  /* Allocate arrays to hold the data of all matrix elements. */
  if (!MMSparseMatrixAllocateMemory(B)) mexErrMsgTxt("Unable to allocate matrix!");
  if (B->i == NULL || B->j == NULL || B->ReValue == NULL || (B->ImValue == NULL && APi != NULL)) mexErrMsgTxt ("Unable to allocate Mondriaan matrix arrays!");
  
  /* Fill the arrays with data from A. */
  i = 0;
  
  for (j = 0; j < B->n && AJc[j] < (size_t)B->NrNzElts; j++) {
    for (k = AJc[j + 1] - AJc[j]; k-- > 0; ) {
      B->i[i] = AIr[i];
      B->j[i] = j;
      B->ReValue[i] = APr[i];
      
      if (B->ImValue != NULL) B->ImValue[i] = APi[i];
      
      i++;
    }
  }
  
  return B;
}
/* Compare function necessary to order triplets in a fashion that is compatible with the Matlab sparse matrix format. */
int CompareTriplets(const void *p1, const void *p2) {
  const struct MondriaanTriplet *t1, *t2;
  
  t1 = (struct MondriaanTriplet *)p1;
  t2 = (struct MondriaanTriplet *)p2;
  
  if (t1->Column != t2->Column) return t1->Column - t2->Column;
  
  return t1->Row - t2->Row;
}


/* This function converts a Mondriaan sparse matrix to a Matlab sparse matrix, Triplets are already created. */
mxArray *ConvertTripletsToMatlab(struct MondriaanTriplet *Triplets, const struct sparsematrix *B) {
  mxArray *A;
  mwIndex *AIr, *AJc;
  double *APr, *APi;
  int CurrentColumn;
  long i;
  
  if (Triplets == NULL) mexErrMsgTxt("Null variable pointer!");
  
  /* Sort them in a Matlab friendly way. */
  qsort(Triplets, B->NrNzElts, sizeof (struct MondriaanTriplet), CompareTriplets);
  
  /* Allocate Matlab matrix and obtain pointers to its real data, imaginary data, row index, and column count arrays respectively. */
  A = mxCreateSparse(B->m, B->n, B->NrNzElts, B->ImValue == NULL ? mxREAL : mxCOMPLEX);
  
  if (A == NULL) mexErrMsgTxt("Unable to allocate Matlab matrix!");
  
  APr = mxGetPr (A);
  APi = mxGetPi (A);
  AIr = mxGetIr (A);
  AJc = mxGetJc (A);
  
  /* Write triplets to the Matlab matrix. */
  CurrentColumn = 0;
  *AJc++ = 0;
  
  for (i = 0; i < B->NrNzElts; i++) {
    *AIr++ = Triplets[i].Row;
    *APr++ = Triplets[i].ReValue;
    if (APi) *APi++ = Triplets[i].ImValue;
    
    /* Check whether or not we need to advance to the next column. */
    while (CurrentColumn < Triplets[i].Column) {
      *AJc++ = i;
      CurrentColumn++;
    }
  }
  
  if (CurrentColumn > B->n) mexErrMsgTxt( "Current column advanced farther than end of matrix!" );
  if (i != B->NrNzElts)     mexErrMsgTxt( "Not all nonzeroes are written into Matlab matrix!"   );

        /* This ensures exactly n writes to AJc in this loop together with the
           while loop above. Note that before the for loop above, the 0th element
           already has been set, thus totalling n+1 elements in AJc, so the
           correct number of elements is written. Also, the below loop fires at
           least once, since CurrentColumn is 0-based (and exits above for loop
           at value n-1, at most). */
  for ( ; CurrentColumn < B->n; CurrentColumn++)
    *AJc++ = B->NrNzElts;
  
  free(Triplets);
  
  return A;
}

/* This function converts a Mondriaan sparse matrix to a Matlab sparse matrix. */
mxArray *ConvertMondriaanToMatlab(const struct sparsematrix *B) {
  struct MondriaanTriplet *Triplets;
  long i;
  
  if (B == NULL) mexErrMsgTxt("Null variable pointer!");
  
  /* Extract all non-zero entries. */
  Triplets = (struct MondriaanTriplet *)malloc(B->NrNzElts*sizeof (struct MondriaanTriplet));
  
  if (Triplets == NULL) mexErrMsgTxt("Unable to allocate triplets!");
  
  for (i = 0; i < B->NrNzElts; i++) {
    Triplets[i].Row = B->i[i];
    Triplets[i].Column = B->j[i];
    Triplets[i].ReValue = B->ReValue[i];
    if (B->ImValue) Triplets[i].ImValue = B->ImValue[i];
    else Triplets[i].ImValue = 0.0;
  }
  return ConvertTripletsToMatlab( Triplets, B );
} 

/* This function provides the actual Matlab interface. */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  struct sparsematrix* MondriaanMatrix;
  int i;

  /* converting the matrix from Matlab to Mondriaan */
  MondriaanMatrix = ConvertMatlabToMondriaan(prhs[0]);

  /* computing the length of the priority vector */
  int length = MondriaanMatrix->m+MondriaanMatrix->n;

  /* getting the vector as double* */
  double* inputVec = mxGetPr(prhs[1]);

  /* switching from mondriaan numbering of rows/cols to C */
  for(i=0;i<length;i++) inputVec[i] -= 1.0;

  /* explicit conversion of double* to long* */
  long* vec = double_array_to_long(inputVec,length);
  
  /* switching from Matlab matrix storage (ascending columns) to ascending rows */
  struct sparsematrixplus mat = reorder_row_incr(MondriaanMatrix);
  
  /* performing split */
  struct twomatrices two = overpaint(&(mat.matrix),vec); 

  /* separating the two parts */
  struct sparsematrix matrix = two.Ac;
  struct sparsematrix matrix2 = two.Ar;
  
  /* converting back from Mondriaan to Matlab   */
  plhs[0] = ConvertMondriaanToMatlab(&matrix);
  plhs[1] = ConvertMondriaanToMatlab(&matrix2);
  
  vecfreed(inputVec);
  vecfreel(vec);
  MMDeleteSparseMatrix(MondriaanMatrix);
}

