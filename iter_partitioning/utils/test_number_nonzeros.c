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

	print_vec_inline(matrix.i,matrix.NrNzElts);
	print_vec_inline(matrix.j,matrix.NrNzElts);

	long* nonzeros = number_nonzeros(&matrix);
	printf("-----------\n");

	print_vec_inline(nonzeros,matrix.m+matrix.n);

	vecfreel(nonzeros); 
	MMDeleteSparseMatrix(&matrix);
	return 0;
}
