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
	
	struct opts Options;	
	SetDefaultOptions(&Options);
	PstartInit(&matrix,2);
	if(!DistributeMatrixMondriaan(&matrix, 2, 0.03, &Options, NULL)){
		printf("uh oh\n");
		exit(1);
	}

	print_vec_inline(matrix.Pstart,2);
	print_matrix(matrix);
	printf("---\n");
	struct sparsematrix new_matrix = partition_to_matrix(&matrix);
	print_matrix(new_matrix);

	MMDeleteSparseMatrix(&matrix);
	MMDeleteSparseMatrix(&new_matrix);
	return 0;
}
