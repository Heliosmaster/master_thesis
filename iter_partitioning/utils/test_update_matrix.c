#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <Mondriaan.h>
#include "utils.c"

int main(){
  /* srand(time(NULL)); */
  /* reading the matrix from file */
  FILE* File;
  struct sparsematrix matrix;
  File = fopen("../../matrices/test_matrix.mtx", "r");
  if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
  fclose(File);

  /* getting the ICS version of A */

  struct sparsematrixplus reordering = reorder_col_incr(&matrix);

  struct sparsematrix matrix2 = reordering.matrix;

  /* getting the increments */
  long* incr_rows = get_increment_rows(&matrix);
  long* incr_cols = get_increment_cols(&matrix2);

  /* print out */

  printf("Original matrix:\n");
  print_matrix(matrix);
  printf("-----------------\n");

  printf("Trying to put 10 in the 3rd row of A\n");
  update_rows(&matrix,incr_rows,3,10);
  print_matrix(matrix);
  printf("-----------------\n");
 
  printf("Trying to put 11 in the 2nd col of B\n");
  update_cols(&matrix2,incr_cols,2,11);
  print_matrix(matrix2);
  printf("-----------------\n");

  printf("Trying to put 11 in the 2nd col of A using link\n");
  update_cols_link(&matrix2,&matrix,incr_cols,2,11,reordering.perm);
  print_matrix(matrix);
  printf("-----------------\n");  

  long* perm2 = reverse_perm(reordering.perm,matrix2.NrNzElts);
  printf("Trying to put 10 in the 3rd row of B using link\n");
  update_rows_link(&matrix,&matrix2,incr_rows,3,10,perm2);
  print_matrix(matrix2);
  printf("-----------------\n"); 

  MMDeleteSparseMatrix(&matrix);
  MMDeleteSparseMatrix(&matrix2);
  vecfreel(incr_rows);
  vecfreel(incr_cols);
  vecfreel(perm2); 
}
