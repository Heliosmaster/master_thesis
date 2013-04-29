#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <Mondriaan.h>
#include "utils.c"

/*
* method that returns a random integer in [0,bound]
*/
int randi(int bound){
  return ceil(rand()*1.0/RAND_MAX*bound);
}

/*
* adding xor functionality to C (which does not support operator overloading)
*/
int xor(int a, int b){
  return (!a && b) || (a && !b);
}



/*
* methods to find out which rows/cols 
* (depending on whether the input vector is i or j)
* are empty / nonempty (and how many nonzeros they have)
*
* input = i/j
* NrNzElts = length(input)
* size = m/n
*/
long* nnz(long* input, int NrNzElts, int size){
  /* initialization of the output vector */
  long* nonz = vecallocl(size);

  /* filling out the vector with 0s (o/w MATLAB does not empty it) */
  int index;
  for(index=0;index<size;index++)
    nonz[index] = 0;

  /* sweep of the input vector: increased the counter for every index found */
  index = 0;
  while(index<NrNzElts){
    nonz[input[index]]++;
    index++;
  }
  return nonz;
}

/*
* function that assigns the nonzeros of matrix either to Ar or Ac
*/
struct twomatrices localview(struct sparsematrix* matrix){

  /* dividing between A1 and A2 */
  struct twomatrices A = split_matrix(matrix,1.0,2.0);

  struct sparsematrix* A1 = &(A.Ar);
  struct sparsematrix* A2 = &(A.Ac);

  /* explicit saving of m,n for brevity */
  int m = matrix->m;
  int n = matrix->n;

  /* 
  * building the bookkeeping vectors
  * nzXr = nonzeros in the rows of AX
  * nzXc = nonzeros in the columns of AX
  * nzr,nzc = nonzeros in row/col of matrix
  */
  long* nz1r = nnz(A1->i, A1->NrNzElts, m);
  long* nz2r = nnz(A2->i, A2->NrNzElts, m);
  long* nzr = nnz(matrix->i, matrix->NrNzElts, m);

  long* nz1c = nnz(A1->j, A1->NrNzElts, n);
  long* nz2c = nnz(A2->j, A2->NrNzElts, n);
  long* nzc = nnz(matrix->j, matrix->NrNzElts, n);

  /* storing the number of nonzeros that have to be assigned */
  int len = matrix->NrNzElts;
  
  /* 
  * initialization of the new vectors to be populated
  * assuming everything is assigned to one and the other stays empty
  * the max size is matrix.NrNzElts (len)
  */
  long* ir = vecallocl(len);
  long* jr = vecallocl(len);
  long* ic = vecallocl(len);
  long* jc = vecallocl(len);

  /* counters for filling of ir,jr and ic,jc */
  int index_r = 0;
  int index_c = 0;
  
  int i,j,k;
  k = 0;
  while(len>0){

    /* TODO k randomly chosen between 0 and len */
    /* k = randi(len); */

    /* computing explicitly row and column of the k-th element of the matrix */
    i = matrix->i[k];
    j = matrix->j[k];

    /* computing whether i,j are split */
    int rowsplit = (nz1r[i] && nz2r[i]);
    int colsplit = (nz1c[j] && nz2c[j]);

    /* actual assignment of the nonzero */
    if (!xor(rowsplit,colsplit)){
      if (nzr[i]<nzc[j]){
        ir[index_r] = i;
        jr[index_r] = j;
        index_r++;
      } else {
        ic[index_c] = i;
        jc[index_c] = j;
        index_c++;
      }
    } else {
      if (rowsplit) {
        ic[index_c] = i;
        jc[index_c] = j;
        index_c++;
      } else {
        ir[index_r] = i;
        jr[index_r] = j;
        index_r++;
      }
    }
    /*
    * putting the last element that could be chosen instead of the
    * k-th one, and we reduce the interval for randi by 1
    */
     /* matrix.i[k] = matrix.i[len-1];
    matrix.j[k] = matrix.j[len-1]; */
    k++;
    len--;
  }

  /* creation of vectors of the right size */
  long* ir_n = vecallocl(index_r);
  long* jr_n = vecallocl(index_r);
  long* ic_n = vecallocl(index_c);
  long* jc_n = vecallocl(index_c);

  /* copying only the filled part */
  memcpy(ir_n,ir,index_r*SZLONG);
  memcpy(jr_n,jr,index_r*SZLONG);
  memcpy(ic_n,ic,index_c*SZLONG);
  memcpy(jc_n,jc,index_c*SZLONG);

  /* creating the (dummy) values for the nonzeros */
  double* val_r = vecallocd(index_r);
  double* valc_r = vecallocd(index_r);
  double* val_c = vecallocd(index_c);
  double* valc_c = vecallocd(index_c);

  for(k=0;k<index_r;k++){
    val_r[k] = 1.0;
    valc_r[k] = 0.0;
  }
  for(k=0;k<index_c;k++){
    val_c[k] = 1.0;
    valc_c[k] = 0.0;
  }

  /* explicit creation of the final matrices */
  struct sparsematrix Ar;
  Ar.NrNzElts = index_r;
  Ar.m = m;
  Ar.n = n;
  Ar.i = ir_n;
  Ar.j = jr_n;
  Ar.ReValue = val_r;
  Ar.ImValue = valc_r;

  struct sparsematrix Ac;
  Ac.NrNzElts = index_c;
  Ac.i = ic_n;
  Ac.j = jc_n;
  Ac.m = m;
  Ac.n = n;
  Ac.ReValue = val_c;
  Ac.ImValue = valc_c;
  
  /* freeing memory from unnecessary arrays */
  vecfreel(ir);
  vecfreel(jr);
  vecfreel(ic);
  vecfreel(jc);

  vecfreel(nz1c);
  vecfreel(nz2c);
  vecfreel(nzc);

  vecfreel(nz1r);
  vecfreel(nz2r);
  vecfreel(nzr);

  /* explicit construction of the output */
  struct twomatrices output;

  output.Ar = Ar;
  output.Ac = Ac;

  return output;
}

