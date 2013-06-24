#include "overpaint.h"
#include "../utils/utils.h"
#include "../utils/createB.h"

struct twomatrices DoMondriaan(struct sparsematrix matrix, int SplitStrategy){
	struct opts Options;
	SetDefaultOptions(&Options);

	if (SplitStrategy == 5) Options.SplitStrategy = OneDimCol;
	else if (SplitStrategy == 8) Options.SplitStrategy = MediumGrain;
	else if (SplitStrategy == -1) {
		printf("Default split strategy\n");
	}
	else{
		printf("Wrong Split Strategy!\n");
		exit(1);
	}
	if (!ApplyOptions(&Options))
	{
		printf("Invalid options!\n");
		exit(1);
	}
/*	matrix.Pstart = vecallocl(3);*/
	if(!DistributeMatrixMondriaan(&matrix, 2, 0.03, &Options, NULL)){
		printf("uh oh\n");
		exit(1);
	}

	printf("%ld %ld %ld\n",matrix.Pstart[0],matrix.Pstart[1],matrix.Pstart[2]);
	int k;
	struct sparsematrix A1;
	MMSparseMatrixInit(&A1);
	A1.m = matrix.m;
	A1.n = matrix.n;
	A1.NrNzElts = matrix.Pstart[1]-matrix.Pstart[0];

	A1.i = vecallocl(A1.NrNzElts);
	A1.j = vecallocl(A1.NrNzElts);
	A1.ReValue = vecallocd(A1.NrNzElts);

	int start = matrix.Pstart[0];
	for(k=0;k<A1.NrNzElts;k++){
		A1.i[k] = matrix.i[start+k];
		A1.j[k] = matrix.j[start+k];
		A1.ReValue[k] = 1.0;
	}

	struct sparsematrix A2;
	MMSparseMatrixInit(&A2);
	A2.m = matrix.m;
	A2.n = matrix.n;
	A2.NrNzElts = matrix.Pstart[2]-matrix.Pstart[1];

	A2.i = vecallocl(A2.NrNzElts);
	A2.j = vecallocl(A2.NrNzElts);
	A2.ReValue = vecallocd(A2.NrNzElts);

	start = matrix.Pstart[1];
	for(k=0;k<A2.NrNzElts;k++){
		A2.i[k] = matrix.i[start+k];
		A2.j[k] = matrix.j[start+k];
		A2.ReValue[k] = 2.0;
	}

	/* Variables used for calculating the communication volume. */
	long ComVolumeRow, ComVolumeCol, Dummy;

	/* Calculate the communication volume. */
	CalcCom(&matrix, NULL, ROW, &ComVolumeRow, &Dummy, &Dummy, &Dummy, &Dummy);
	CalcCom(&matrix, NULL, COL, &ComVolumeCol, &Dummy, &Dummy, &Dummy, &Dummy);
	printf("This distribution has a total communication volume equal to %ld.\n", ComVolumeRow + ComVolumeCol);

	struct twomatrices two;
	two.Ac = A1;
	two.Ar = A2;
	return two;
}

int main(int argc, char* argv[]){
	FILE* File;
	struct sparsematrix matrix;
	File = fopen("../../matrices/dfl001.mtx", "r");
	/* File = fopen("../../matrices/tbdlinux.mtx", "r"); */
	if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
	fclose(File);
	int m = matrix.m;
	int n = matrix.n;

	if(matrix.ReValue == NULL){
		matrix.ReValue = vecallocd(matrix.NrNzElts);
		int j;
		for(j=0;j<matrix.NrNzElts;j++) matrix.ReValue[j] = 0.0;
	}

	long* vec = random_permutation(m+n);
	/* int i;
		 long* vec = vecallocl(m+n);
		 for(i=0;i<m+n;i++) vec[i]=i;*/

	/* explicit computation of Ar and Ac with the overpaint method */
	struct sparsematrixplus m2plus = reorder_row_incr(&matrix);
	struct sparsematrix matrix2 = m2plus.matrix;
	struct twomatrices one = overpaint(&matrix2,vec);

	struct sparsematrix B = createB(&(one.Ac),&(one.Ar));

	struct twomatrices two = DoMondriaan(matrix,-1);

	MMDeleteSparseMatrix(&two.Ar);
	MMDeleteSparseMatrix(&two.Ac);

	MMDeleteSparseMatrix(&B);
	MMDeleteSparseMatrix(&one.Ar);
	MMDeleteSparseMatrix(&one.Ac);
	MMDeleteSparseMatrix(&matrix2);
	vecfreel(m2plus.perm);
	vecfreel(vec);	
	MMDeleteSparseMatrix(&matrix);
	return 0;
}

