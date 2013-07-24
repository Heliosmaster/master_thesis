#include <string.h>
#include <unistd.h>
#include "overpaint.h"
#include "../utils/utils.h"
#include "../utils/createB.h"
#include "priority_vector.h"

int main(int argc, char* argv[]){
	char input[100];
	if (argc > 1) strcpy(input,argv[1]);
	else strcpy(input,"../../matrices/test_matrix.mtx");
	char temp_name[100] = "tmp.mtx";
	FILE* File;
	struct sparsematrix matrix;
	File = fopen(input, "r");
	if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
	fclose(File);

	if(matrix.ReValue == NULL){
		matrix.ReValue = vecallocd(matrix.NrNzElts);
		int j;
		for(j=0;j<matrix.NrNzElts;j++) matrix.ReValue[j] = 0.0;
	}
	srand(time(NULL));

	struct opts Options;
	print_label_vector(1,1,0);
	SetOptionsFromFile(&Options,"Mondriaan.defaults");
	int i;
	int outer_iter = 10;
	int inner_iter = 5;

	long* outer_vec = vecallocl(outer_iter);

	for(i=0;i<outer_iter;i++){
		struct sparsematrix temp_matrix = matrix;

		int comm_value;
		struct sparsematrix init_part = ExecuteMondriaan(&temp_matrix,-1,&Options,&comm_value); 
		copyHeader(&matrix,&init_part);

		int k;

		long* inner_vec = vecallocl(inner_iter);
		for(k=0;k<inner_iter;k++){

			long* vec = choose_vector(1,&init_part,1,0);
			struct twomatrices one = overpaint(&init_part,vec);
			struct sparsematrix B = createB(&(one.Ac),&(one.Ar));
			copyHeader(&matrix,&B);

			File = fopen(temp_name, "w");
			if (!MMWriteSparseMatrix(&B,File,NULL,&Options)) printf("Unable to write input matrix!\n");
			fclose(File);

			MMDeleteSparseMatrix(&B);

			File = fopen(temp_name, "r");
			if (!MMReadSparseMatrix(File, &B)) printf("Unable to read input matrix!\n");
			fclose(File);
			remove(temp_name);	

			struct sparsematrix new_matrix = ExecuteMondriaan(&B,5,&Options,&comm_value);

			inner_vec[k] = comm_value;
			printf("%d \t", comm_value); fflush(stdout);

			MMDeleteSparseMatrix(&new_matrix);
			MMDeleteSparseMatrix(&B);
			MMDeleteSparseMatrix(&one.Ar);
			MMDeleteSparseMatrix(&one.Ac);
			vecfreel(vec);

		}
		double mean = ar_mean(inner_vec,inner_iter);
		outer_vec[i]=mean;
		printf("| \t avg: %5.2f\n",mean);
		/*		MMDeleteSparseMatrix(&temp_matrix);*/
		MMDeleteSparseMatrix(&init_part);
		/*		sleep(1);*/
	}
	printf("total average: %5.2f\n",ar_mean(outer_vec,outer_iter));
	MMDeleteSparseMatrix(&matrix);
	return 0;
}
