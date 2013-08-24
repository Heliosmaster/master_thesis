#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <Mondriaan.h>
#include "utils.h"

long newMondriaan(struct sparsematrix* matrix, int SplitStrategy) {
	struct opts Options; /* The Mondriaan options */
	struct sparsematrix A; /* The Matrix;-) */

	long MinNrNzElts, MaxNrNzElts; /* minimum, maximum number of nonzero elements 
																		per processor */
	double AvgNrNzElts; /* average number of nonzero matrix elements per processor */

	long int *temp;
	long q, nzq;     /* processor number and its corresponding number of nonzeros */
	int weighted, symmetric; /* boolean registering whether the input matrix
															was weighted, symmetric */

	long int *u_proc, *v_proc;   /* vector distribution for u, v */

	FILE *File = NULL;

	/* Get the parameters from the command line and initialise Options */
	SetDefaultOptions(&Options);

	if (!SetOptionsFromFile(&Options, "Mondriaan.defaults")) {
		fprintf(stderr, "main(): warning, cannot set options from 'Mondriaan.defaults', using default options and creating standard 'Mondriaan.defaults'!\n");

		File = fopen("Mondriaan.defaults", "w");

		if (File != NULL) {
			ExportDefaultOptions(File);
			SetDefaultOptions(&Options);
			fclose(File);
		}
		else {
			fprintf(stderr, "main(): Unable to create 'Mondriaan.defaults'!\n");
		}
	}
	/*	Options.matrix = matrix;*/
	Options.P = 2;
	Options.eps = 0.03;
	if(SplitStrategy == 8) Options.SplitStrategy = MediumGrain;
	if(SplitStrategy == 5) Options.SplitStrategy = OneDimCol;

	if (!ApplyOptions(&Options)) {
		fprintf(stderr, "main(): could not apply given options!\n");
		exit(-1);
	}
	/*
		 File = fopen(Options.matrix, "r");

		 if (!File) {
		 fprintf(stderr, "main(): Unable to open '%s' for reading!\n", Options.matrix);
		 exit(-1);
		 }

		 if (!MMReadSparseMatrix(File, &A)) {
		 fprintf(stderr, "main(): Could not read matrix!\n");
		 exit(-1);
		 }

		 fclose(File);
		 */
	A = *matrix;
	/* Remove duplicate nonzeros by adding them */
	if (!SparseMatrixRemoveDuplicates(&A)) {
		fprintf(stderr, "main(): Unable to remove duplicates!\n");
		exit(-1);
	}

	/* Check if matrix A is already distributed */
	if (A.MMTypeCode[0] == 'D') {
		/* Matrix will be partitioned again */
		fprintf(stderr, "Warning: Matrix '%s' already distributed !\n", 
				Options.matrix);
		fprintf(stderr, "         (Ignoring current partitions)\n"); 

		A.NrProcs = 0;
		if (A.Pstart != NULL)
			free(A.Pstart);
		A.Pstart = NULL;
	}

	/* Check if matrix is weighted (thus representing a hypergraph).
		 In that case, it must have n column weights (representing vertex weights), 
		 0 row weights and the split strategy must be onedimcol */

	if (A.MMTypeCode[0] == 'W' && A.NrColWeights != A.n) {
		fprintf(stderr, "main(): Weighted matrix with NrColWeights != n!\n");
		exit(-1);
	}

	if (A.MMTypeCode[0] == 'W' && A.NrRowWeights != 0) {
		fprintf(stderr, "Warning: Matrix '%s' has row weights!\n",
				Options.matrix);
		fprintf(stderr, "         Row-weighted column partitioning not yet implemented\n");
		fprintf(stderr, "         (Ignoring row weights)\n");

		A.NrRowWeights = 0;
		if (A.RowWeights != NULL)
			free(A.RowWeights);
		A.RowWeights = NULL;
	}

	if (A.MMTypeCode[0] == 'W' && Options.SplitStrategy != OneDimCol) {
		fprintf(stderr, "Warning: Matrix '%s' is a weighted matrix!\n", Options.matrix);
		fprintf(stderr, "         must be partitioned by onedimcol strategy\n");
		fprintf(stderr, "         (Ignoring requested split strategy)\n");
		Options.SplitStrategy = OneDimCol;
	}

	/* Register whether the input matrix was weighted, since the object type code will
		 be changed by the partitioning procedure to the code 'D' for a distributed matrix */
	if (A.MMTypeCode[0] == 'W')
		weighted = TRUE;
	else
		weighted = FALSE;

	/* Register whether the input matrix was symmetric, since the symmetry type code will
		 be changed by the conversion to full, to the code 'G' for a general matrix */
	if (A.m == A.n && 
			(A.MMTypeCode[3]=='S' || A.MMTypeCode[3]=='K' || A.MMTypeCode[3]=='H')) {
		symmetric = TRUE; 
	} else {
		symmetric = FALSE;
		if (Options.SplitStrategy == SFineGrain) {
			fprintf(stderr, "Error: Symmetric finegrain can only be used on symmetric input matrices!\n");
			exit(-1);
		}
	}

	if (symmetric) {
		if (Options.SymmetricMatrix_UseSingleEntry == SingleEntNo)
			SparseMatrixSymmetric2Full(&A); 
		else if (Options.SplitStrategy == SFineGrain)
			SparseMatrixSymmetricRandom2Lower(&A);
		else if (Options.SymmetricMatrix_SingleEntryType == ETypeRandom)
			SparseMatrixSymmetricLower2Random(&A);
	}

	if (Options.SplitStrategy == SFineGrain && Options.SymmetricMatrix_SingleEntryType == ETypeRandom)
		printf("Warning: Symmetric finegrain requires lower-triangular format of symmetric matrix;\n         Random single entry type option is overridden.\n");

	/* If the matrix is square, add the dummies if requested.
		 This may lead to an enhanced vector distribution in the case of
		 an equal distribution of the input and output vectors.  */
	if (A.m == A.n && 
			Options.SquareMatrix_DistributeVectorsEqual == EqVecYes &&
			Options.SquareMatrix_DistributeVectorsEqual_AddDummies == DumYes)
		AddDummiesToSparseMatrix(&A);

	/* Set the number of processors */
	A.NrProcs = Options.P;

	/* Initialise Pstart with all nonzeros in processor 0 */
	A.Pstart = (long *) malloc((A.NrProcs+1) * sizeof(long));
	if (A.Pstart == NULL) {
		fprintf(stderr, "main(): Not enough memory for Pstart!\n");
		exit(-1);
	}

	A.Pstart[0] = 0;
	for (q = 1; q <= A.NrProcs; q++)
		A.Pstart[q] = A.NrNzElts;

	/**** Distribute the matrix (and time it) ****/

	if (!DistributeMatrixMondriaan(&A, A.NrProcs, Options.eps, &Options, 0)) {
		fprintf(stderr, "main(): Unable to distribute matrix!\n");
		exit(-1);
	}

	/* Convert randomly represented symmetric matrix to standard
		 lower triangular form */
/*	if (symmetric &&
			Options.SymmetricMatrix_UseSingleEntry == SingleEntYes &&
			Options.SymmetricMatrix_SingleEntryType == ETypeRandom)
		SparseMatrixSymmetricRandom2Lower(&A);*/

	long ComVolumeRow, ComVolumeCol, Dummy;

	CalcCom(&A, NULL, ROW, &ComVolumeRow, &Dummy, &Dummy, &Dummy, &Dummy);
	CalcCom(&A, NULL, COL, &ComVolumeCol, &Dummy, &Dummy, &Dummy, &Dummy);
	long comm_value = ComVolumeRow+ComVolumeCol;
	printf("comm: %ld\n",comm_value); fflush(stdout);
/*	free(A.Pstart);*/
	MMDeleteSparseMatrix(&A);
	return comm_value;
} /* end main */

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
		initial_vec[i] = newMondriaan(&B,8);
		/*MMDeleteSparseMatrix(&B);*/
		
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
