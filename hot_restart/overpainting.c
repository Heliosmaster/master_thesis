#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <Mondriaan.h>
#include "../utils.c"


struct twomatrices overpaint(struct sparsematrix* A, long* vec){
  int m = A->m;
  int n = A->n;

  struct sparsematrixplus matrixplus = reorder_col_incr(A);
  struct sparsematrix* B = &(matrixplus.matrix);
  long* BtoA = matrixplus.perm;

  int i,k;

  for(i=m+n-1;i>=0;i--){
    k = vec[i];
    if (k<m){
      /* it's a row*/
      update_rows(A,k,10.0);
    } else {
      /* it's a column */
      update_cols_link(B,A,k-m,11.0,BtoA);
    }
  }

  return split_matrix(A,10.0,11.0);
}
/*
struct twomatrices overpaint_col(struct sparsematrix* A, long* vec){
  int m = A->m;
  int n = A->n;
  int length = A->NrNzElts;

  struct sparsematrixplus matrixplus = reorder_row_incr(A);
  struct sparsematrix* B = &(matrixplus.matrix);
  long* BtoA = matrixplus.perm;
  int i,k;
 

  for(i=length-1;i>=0;i--){
    k = vec[i];
    if (k<m){
      // it's a row
      update_rows_link(B,A,k,10.0,BtoA);
    } else {
      // it's a column 
      update_cols(A,k-m,11.0);
    }
    printf("===%d===\n",length-i-1);
    print_matrix(*A);
  }


  return split_matrix(A,10.0,11.0);
}*/