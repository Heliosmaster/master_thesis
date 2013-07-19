#include <string.h>
#include "overpaint.h"
#include "../utils/utils.h"
#include "../utils/createB.h"
struct twomatrices DoMondriaan(struct sparsematrix matrix, int SplitStrategy, struct opts* Options){
	if (SplitStrategy == 5) Options->SplitStrategy = OneDimCol;
	else if (SplitStrategy == 8) Options->SplitStrategy = MediumGrain;
	else if (SplitStrategy == -1) {
		printf("Default split strategy\n");
	}
	else{
		printf("Wrong Split Strategy!\n");
		exit(1);
	}
	if (!ApplyOptions(Options)){
		printf("Invalid options!\n");
		exit(1);
	}
	PstartInit(&matrix,2);
	if(!DistributeMatrixMondriaan(&matrix, 2, 0.03, Options, NULL)){
		printf("uh oh\n");
		exit(1);
	}
	printf("%ld %ld %ld\n",matrix.Pstart[0],matrix.Pstart[1],matrix.Pstart[2]);
	struct sparsematrix A1 = assignMatrix(&matrix,1);
	struct sparsematrix A2 = assignMatrix(&matrix,2);

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
	char input[100];
	if (argc > 1){
		strcpy(input,argv[1]);
	} else {
		strcpy(input,"../../matrices/test_matrix.mtx");
	}
	char temp_name[100] = "tmp.mtx";
	FILE* File;
	struct sparsematrix matrix;
	File = fopen(input, "r");
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
	srand(time(NULL));
	long* vec = random_permutation(m+n);
	/*int i;
		long* vec = vecallocl(m+n);
		for(i=0;i<m+n;i++) vec[i]=m+n-i;
		*/
	/* explicit computation of Ar and Ac with the overpaint method */
	struct sparsematrixplus m2plus = reorder_row_incr(&matrix);
	struct sparsematrix matrix2 = m2plus.matrix;
	struct twomatrices one = overpaint(&matrix2,vec);
	struct sparsematrix B = createB(&(one.Ac),&(one.Ar));
	struct opts Options;
	/* SetDefaultOptions(&Options);*/
	SetOptionsFromFile(&Options,"Mondriaan.defaults");

	copyHeader(&matrix,&B);

	File = fopen(temp_name, "w");
	if (!MMWriteSparseMatrix(&B,File,NULL,&Options)) printf("Unable to write input matrix!\n");
	fclose(File);

	MMDeleteSparseMatrix(&B);

	File = fopen(temp_name, "r");
	if (!MMReadSparseMatrix(File, &B)) printf("Unable to read input matrix!\n");
	fclose(File);
	remove(temp_name);	
	struct twomatrices two = DoMondriaan(B,-1,&Options);

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

