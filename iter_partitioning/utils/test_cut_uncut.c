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

	printf("Initial split matrix:\n\n");
	print_matrix(two.Ar);
	printf("---\n");
	print_matrix(two.Ac);

	long* split = cut_vector(&two.Ar,&two.Ac);

	printf("\nvector of splits:\n");
	int i=0;
	for(i=0;i<matrix.m;i++)printf("%ld ",split[i]);
	printf("| ");
	for(;i<matrix.m+matrix.n;i++) printf("%ld ",split[i]);
	printf("\n\n");

	int len,len2;
	long* cut_vec = cut_uncut_part(split,matrix.m+matrix.n,1,&len);
	long* uncut_vec = cut_uncut_part(split,matrix.m+matrix.n,0,&len2);

	printf("cut indices:\t ");	print_vec_inline(cut_vec,len);
	printf("uncut_indices:\t "); print_vec_inline(uncut_vec,len2);

	vecfreel(uncut_vec);
	vecfreel(cut_vec);
	vecfreel(split);
	MMDeleteSparseMatrix(&matrix);
	MMDeleteSparseMatrix(&two.Ar);
	MMDeleteSparseMatrix(&two.Ac);
	return 0;
}
