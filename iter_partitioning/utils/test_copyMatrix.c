#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <time.h>
#include <Mondriaan.h>
#include "createB.h"

int main(){
  /* srand(time(NULL)); */
  /* reading the matrix from file */
  FILE* File;
  struct sparsematrix matrix;
  File = fopen("../../matrices/test_matrix.mtx", "r");
  if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
  fclose(File);

  /* splitting the matrix following the nonzero values (1 and 2) */
	struct sparsematrix new_matrix = copyMatrix(&matrix);
	print_matrix(new_matrix);

  /* creating the B matrix and printing it */
  MMDeleteSparseMatrix(&matrix);
  MMDeleteSparseMatrix(&new_matrix);
	return 0;
}
