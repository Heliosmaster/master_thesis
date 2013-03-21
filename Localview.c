#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <Mondriaan.h>
#include "utils.c"

struct TwoParts {
  struct sparsematrix Ar, Ac;
};

void print_matrix(struct sparsematrix matrix){
  int k;
  for(k=0;k<matrix.NrNzElts;k++) printf("(%ld,%ld)=%f\n", matrix.i[k]+1,matrix.j[k]+1,matrix.ReValue[k]);
}

void print_vectorl(long* vec, int length){
  int i;
  for(i=0;i<length;i++)
    printf("%d: %ld\n",i+1,vec[i]);
}

/*
* method that splits the two parts of A which have value 1
* and value two
*/
struct TwoParts split1and2(struct sparsematrix A){

  int k;
  struct TwoParts output;

  struct sparsematrix A1, A2;

  int max1=0;
  int max2=0;

  // initial sweep of the matrix to see how long should be the vectors
  for(k=0;k<A.NrNzElts;k++) (A.ReValue[k] == 2.0) ? max2++ : max1++;
  
  //initialization of the vectors
  long *i1 = vecallocl(max1);
  long *j1 = vecallocl(max1);
  double *v1 = vecallocd(max1);
  long *i2 = vecallocl(max2);
  long *j2 = vecallocl(max2);
  double *v2 = vecallocd(max2);

  // indices to populate i and j
  int index1=0;
  int index2=0;
  for(k=0;k<A.NrNzElts;k++){
    if (A.ReValue[k] == 2.0 ){
      i2[index2] = A.i[k];
      j2[index2] = A.j[k];
      v2[index2] = 2.0;
      index2++;
    }
    else {
      i1[index1] = A.i[k];
      j1[index1] = A.j[k];
      v1[index1] = 1.0;
      index1++;
    }
  }

  A1.m = A.m;
  A2.m = A.m;

  A1.n = A.n;
  A2.n = A.n;
  
  A1.NrNzElts = max1;
  A2.NrNzElts = max2;

  A1.i = i1;
  A1.j = j1;

  A2.i = i2;
  A2.j = j2;

  A1.ReValue = v1;
  A2.ReValue = v2;

  output.Ar = A1;
  output.Ac = A2;

  return output;
}

/*
* methods to find out which rows/cols 
* (depending on whether the input vector is i or j)
* are empty / nonempty
*
* input = i/j
* NrNzElts = length(input)
* size = m/n
*/
long* nnz(long* input, int NrNzElts, int size){
  int index = 0;
  long* nonz = vecallocl(size);
  long value = -1;
  while(index<NrNzElts){
    if (input[index] != value) {
      value = input[index];
      nonz[value] = 1;
    }
    index++;
  }
  return nonz;
}

struct TwoParts localview(struct sparsematrix matrix){
  struct TwoParts A = split1and2(matrix);
  struct sparsematrix A1 = A.Ar;
  struct sparsematrix A2 = A.Ac;

  int m = matrix.m;
  int n = matrix.n;

  struct sparsematrix A1ics =  reorder_col_incr(A1);
  struct sparsematrix A2ics =  reorder_col_incr(A2);

  long* nz1r = nnz(A1.i, A1.NrNzElts, A1.m);
  long* nz2r = nnz(A2.i, A2.NrNzElts, A2.m);
  long* nzr = nnz(matrix.i, matrix.NrNzElts, matrix.m);

  long* nz1c = nnz(A1.j, A1.NrNzElts, A1.n);
  long* nz2c = nnz(A2.j, A2.NrNzElts, A2.n);
  long* nzc = nnz(matrix.j, matrix.NrNzElts, matrix.n);

  // free memory from unnecessary arrays
  vecfreel(nz1c);
  vecfreel(nz2c);
  vecfreel(nzc);

  vecfreel(nz1r);
  vecfreel(nz2r);
  vecfreel(nzr);

  // construct explicitly the output
  struct TwoParts output;
  output.Ar = A.Ar;
  output.Ac = A.Ac;

  return output;
}

int main(){
  FILE* File;
  struct sparsematrix matrix;
  if (!(File = fopen("matrices/test_matrix.mtx", "r"))) printf("Unable to open input matrix! Make sure it's the first parameter to the program\n");
  if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
  fclose(File);

  struct TwoParts two = localview(matrix);

  print_matrix(two.Ar);
  printf("\n\n");
  print_matrix(two.Ac);
  
}
