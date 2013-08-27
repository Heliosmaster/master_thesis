#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <Mondriaan.h>
#include "utils.h"

int main(int argc, char* argv[]){
	/* srand(time(NULL)); */
	/* reading the matrix from file */
	char matrixname;
	if(argc>1) {
		sprintf(&matrixname,"%s",argv[1]);
	}	else {
		sprintf(&matrixname,"%s","../../old_matrices/test_matrix.mtx");
	}

	FILE* File;
	struct sparsematrix A;
	File = fopen(&matrixname, "r");

	if (!MMReadSparseMatrix(File, &A)) printf("Unable to read input matrix!\n");
	fclose(File);


	int i;
	int outer_iter = 20;

	long* initial_vec = vecallocl(outer_iter);


	struct sparsematrix B;
	for(i=0;i<outer_iter;i++){
		B = copyMatrix(&A);
		struct sparsematrix C;
		initial_vec[i] = newMondriaan(&B,8,&C);
		MMDeleteSparseMatrix(&C);
	}
	printf("average initials %5.2f\n",ar_mean(initial_vec,outer_iter));
	vecfreel(initial_vec);
/*	MMDeleteSparseMatrix(&B);*/
	MMDeleteSparseMatrix(&A);

	exit(0);
}
int main2(int argc, char* argv[]){
	/* srand(time(NULL)); */
	/* reading the matrix from file */
	FILE* File;
	struct sparsematrix matrix;
	if(argc>1) {
		File=fopen(argv[1],"r");
	}	else {
		File = fopen("../../matrices/test_matrix.mtx", "r");
	}
	if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
	fclose(File);
	/*
		 if(matrix.ReValue == NULL){
		 matrix.ReValue = vecallocd(matrix.NrNzElts);
		 int j;
		 for(j=0;j<matrix.NrNzElts;j++) matrix.ReValue[j] = 1.0;
		 }
		 */
	/*	printf("nz: %ld\n",matrix->NrNzElts);*/
	/*	srand(time(NULL));*/

	struct opts Options;
	SetOptionsFromFile(&Options,"Mondriaan.defaults");
	int i;
	int outer_iter = 20;

	if(matrix.MMTypeCode[3] == 'S'){
		printf("symmetric matrix!\n");
		SparseMatrixSymmetric2Full(&matrix);
		printf("nnz: %ld\n",matrix.NrNzElts);
	}

	long* initial_vec = vecallocl(outer_iter);

	for(i=0;i<outer_iter;i++){
		/*	struct sparsematrix temp_matrix = *matrix;*/

		long comm_value;
		struct sparsematrix init_part = ExecuteMondriaan(&matrix,8,&Options,&comm_value);
		printf("%ld\n",comm_value); fflush(stdout);	
		initial_vec[i] = comm_value;

		MMDeleteSparseMatrix(&init_part);
	}
	/*	print_vec_inline(initial_vec,outer_iter);*/
	printf("average initials %5.2f\n",ar_mean(initial_vec,outer_iter));
	vecfreel(initial_vec);
	MMDeleteSparseMatrix(&matrix);

	return 0;
}
