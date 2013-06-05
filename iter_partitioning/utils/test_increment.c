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
  File = fopen("../../matrices/cre_b.mtx", "r");
  if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
  fclose(File);

  /* making sure its rows are incremental */
  struct sparsematrixplus m2plus = reorder_row_incr(&matrix);
  struct sparsematrix matrix2 = m2plus.matrix;

  /* getting the increment */
  long* increment = get_increment_rows(&matrix2);
  
  MMDeleteSparseMatrix(&matrix);
  MMDeleteSparseMatrix(&matrix2);
  vecfreel(m2plus.perm);
  vecfreel(increment);

}
