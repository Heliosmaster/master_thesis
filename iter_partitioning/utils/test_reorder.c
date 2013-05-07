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
  File = fopen("../../matrices/m_testbed/dfl001.mtx", "r");
  if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
  fclose(File);

  /* reordering the columns, then the row again */

  struct sparsematrix matrix2 = reorder_col_incr(&matrix).matrix;
  struct sparsematrix matrix3 = reorder_row_incr(&matrix2).matrix;

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
  MMDeleteSparseMatrix(&matrix3);

}
