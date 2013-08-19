#include "po_localview.h"

/*
* function that assigns the nonzeros of matrix either to Ar or Ac
*/
struct twomatrices po_localview(struct sparsematrix* matrix){

  /* explicit saving of m,n for brevity */
  int m = matrix->m;
  int n = matrix->n;

  /* 
  * building the bookkeeping vectors
  * nzr,nzc = nonzeros in row/col of matrix
  */
  long* nzr = nnz(matrix->i, matrix->NrNzElts, m);
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
    /* computing explicitly row and column of the k-th element of the matrix */
    i = matrix->i[k];
    j = matrix->j[k];

      /* actual assignment of the nonzero */
      if (nzr[i]<nzc[j]){
        ir[index_r] = i;
        jr[index_r] = j;
        index_r++;
      } else {
        ic[index_c] = i;
        jc[index_c] = j;
        index_c++;
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
  double* val_c = vecallocd(index_c);

  for(k=0;k<index_r;k++) val_r[k] = 1.0;
  for(k=0;k<index_c;k++) val_c[k] = 1.0;

  /* explicit creation of the final matrices */
  struct sparsematrix Ar;
  MMSparseMatrixInit(&Ar);
  Ar.NrNzElts = index_r;
  Ar.m = m;
  Ar.n = n;
  Ar.i = ir_n;
  Ar.j = jr_n;
  Ar.ReValue = val_r;

  struct sparsematrix Ac;
  MMSparseMatrixInit(&Ac);
  Ac.NrNzElts = index_c;
  Ac.i = ic_n;
  Ac.j = jc_n;
  Ac.m = m;
  Ac.n = n;
  Ac.ReValue = val_c;
  
  /* freeing memory from unnecessary arrays */
  vecfreel(ir);
  vecfreel(jr);
  vecfreel(ic);
  vecfreel(jc);

  vecfreel(nzc);

  vecfreel(nzr);

  /* explicit construction of the output */
  struct twomatrices output;

  output.Ar = Ar;
  output.Ac = Ac;

  return output;
}
