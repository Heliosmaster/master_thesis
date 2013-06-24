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
  File = fopen("../../matrices/test_matrix.mtx", "r");
  if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
  fclose(File);

  struct twomatrices two = split_matrix(&matrix,1.0,2.0);
  print_matrix(two.Ar);
  printf("------------\n");
  print_matrix(two.Ac);

	long* split = get_cut(two.Ar,two.Ac);

	int i=0;
	for(i=0;i<matrix.m;i++)printf("%ld ",split[i]);
	printf("| ");
	for(;i<matrix.m+matrix.n;i++) printf("%ld ",split[i]);
	printf("\n");
	vecfreel(split);
  MMDeleteSparseMatrix(&matrix);
  MMDeleteSparseMatrix(&two.Ar);
  MMDeleteSparseMatrix(&two.Ac);
	return 0;
}
