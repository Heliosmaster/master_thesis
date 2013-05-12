#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <Mondriaan.h>
#include "utils.h"

int main(){
  /* srand(time(NULL)); */
  /* reading the matrix from file */
  FILE* File;
  struct sparsematrix matrix;
  File = fopen("../../matrices/dfl001.mtx", "r");
  if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
  fclose(File);

  /* reordering the columns, then the row again */

  struct sparsematrixplus m2plus = reorder_col_incr(&matrix);
  struct sparsematrix matrix2 = m2plus.matrix;
  struct sparsematrixplus m3plus  = reorder_row_incr(&matrix2);
  struct sparsematrix matrix3 = m3plus.matrix;

  /* printing out all the matrices, first and third should be the same */
/*
  print_matrix(matrix);

  printf("---------------------\n");

  print_matrix(matrix2);

  printf("---------------------\n");

  print_matrix(matrix3);

  printf("---------------------\n");
*/
  MMDeleteSparseMatrix(&matrix);
  MMDeleteSparseMatrix(&matrix2);
  vecfreel(m2plus.perm);
  MMDeleteSparseMatrix(&matrix3);
  vecfreel(m3plus.perm);
}
