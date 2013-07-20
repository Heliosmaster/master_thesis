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


	int len,len2;
	/*long* cut_vec =vecallocl(matrix.m+matrix.n);
	long* uncut_vec = vecallocl(matrix.m+matrix.n);
*/
	long* cut_vec;
	long* uncut_vec;
	cut_and_uncut(&matrix,&cut_vec,&len,&uncut_vec,&len2);

	
	printf("cut indices:\t ");	print_vec_inline(cut_vec,len);
	printf("uncut_indices:\t "); print_vec_inline(uncut_vec,len2);

	vecfreel(uncut_vec);
	vecfreel(cut_vec);
	MMDeleteSparseMatrix(&matrix);
	return 0;
}
