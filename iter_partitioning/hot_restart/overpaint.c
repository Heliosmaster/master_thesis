#include "overpaint.h"
/*
* Given a priority vector "vec" of length m+n, for rows (1,...,m) and columns (m+1,...,m+n),
* assigns the nonzero (i,j) to "row" if i<j (wrt the order in vec), to "column" otherwise.
*
* The complexity is reduced by not checking the priority for every nonzero, but by simply following
* the order imposed by vec backwards, assigning two times each nonzero (the last one will stick,
* which refers to the row/column with higher priority)
*
* The matrix A is supposed to be stored by increasing rows
*/

struct twomatrices overpaint(struct sparsematrix* A, long* vec){

  /* explicit storage of the matrix dimension in local variables */
  int m = A->m;
  int n = A->n;


  /* creation and storage of a copy of the matrix with increasing columns */
  struct sparsematrixplus matrixplus = reorder_col_incr(A);
  struct sparsematrix* B = &(matrixplus.matrix);

  /* explicit storage of the permutation vector of the reordering */
  long* BtoA = matrixplus.perm;

  long* incr_cols = get_increment_cols(B);
  long* incr_rows = get_increment_rows(A);

  int i,k;

  /* main loop, iterating through vec backwards */
  for(i=m+n-1;i>=0;i--){
    /* k is the considered row/column */
    k = vec[i];
    if (k<m){
      /* it's a row, set their value as 10 */
      update_rows(A,incr_rows,k,10.0);
    } else {
      /* it's a column, set their nonzero value as 11 */
      update_cols_link(B,A,incr_cols,k-m,11.0,BtoA);
    }
  }

  /* 
  * starting from the matrix A with nonzero values 10 and 11, splitting the two subparts, creating
  * a sparsematrix struct
  */

  vecfreel(BtoA);
  vecfreel(incr_rows);
  vecfreel(incr_cols);
  MMDeleteSparseMatrix(B);
  return split_matrix(A,10.0,11.0);
}
