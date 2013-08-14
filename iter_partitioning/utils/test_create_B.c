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

  struct twomatrices A = split_matrix(&matrix,1.0,2.0);

  /* creating the B matrix and printing it */
  struct sparsematrix B = createB(&(A.Ac),&(A.Ar));
	print_matrix(B);
  MMDeleteSparseMatrix(&matrix);
  MMDeleteSparseMatrix(&A.Ac);
  MMDeleteSparseMatrix(&A.Ar);
  MMDeleteSparseMatrix(&B);
	return 0;
}
