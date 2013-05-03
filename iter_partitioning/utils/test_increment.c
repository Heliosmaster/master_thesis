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
  File = fopen("../../matrices/dfl001.mtx", "r");
  if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
  fclose(File);

  /* making sure its rows are incremental */
  struct sparsematrix matrix2 = reorder_row_incr(&matrix).matrix;

  /* getting the increment */
  get_increment_rows(&matrix2);

}
