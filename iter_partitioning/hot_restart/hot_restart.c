#include <string.h>
#include <unistd.h>
#include "overpaint.h"
#include "../utils/utils.h"
#include "../utils/createB.h"
#include "priority_vector.h"

int main(int argc, char* argv[]){
	char input[100];
	int method;
	int option1;
	int option2;
	switch(argc){
		case 1:
			strcpy(input,"../../matrices/test_matrix.mtx");
			method = 0;
			option1 = 0;
			option2 = 0;
			break;
		case 2:
			strcpy(input,argv[1]);
			method = 0;
			option1 = 0;
			option2 = 0;
			break;
		case 3:
			strcpy(input,argv[1]);
			method = atoi(argv[2]);
			option1 = 0;
			option2 = 0;
			break;
		case 4:
			strcpy(input,argv[1]);
			method = atoi(argv[2]);
			option1 = atoi(argv[3]);
			option2 = 0;
			break;
		case 5:
			strcpy(input,argv[1]);
			method = atoi(argv[2]);
			option1 = atoi(argv[3]);
			option2 = atoi(argv[4]);
			break;
		default:
			strcpy(input,"../../matrices/test_matrix.mtx");
			method = 0;
			option1 = 0;
			option2 = 0;
	}
	char temp_name[100] = "tmp.mtx";
	FILE* File;
	struct sparsematrix matrix;
	File = fopen(input, "r");
	if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
	fclose(File);

	if(matrix.ReValue == NULL){
		matrix.ReValue = vecallocd(matrix.NrNzElts);
		int j;
		for(j=0;j<matrix.NrNzElts;j++) matrix.ReValue[j] = 1.0;
	}
	srand(time(NULL));

	struct opts Options;
	print_label_vector(method,option1,option2);
	SetOptionsFromFile(&Options,"Mondriaan.defaults");
	int i;
	int outer_iter = 20;
	int inner_iter = 5;

	long* outer_vec = vecallocl(outer_iter);
	long* initial_vec = vecallocl(outer_iter);

	for(i=0;i<outer_iter;i++){
		struct sparsematrix temp_matrix = matrix;

		int comm_value;
		struct sparsematrix init_part = ExecuteMondriaan(&temp_matrix,8,&Options,&comm_value);
		printf("%d \t|\t",comm_value);fflush(stdout);	
		initial_vec[i] = comm_value;
		copyHeader(&matrix,&init_part);

		int k;

		long* inner_vec = vecallocl(inner_iter);
		for(k=0;k<inner_iter;k++){
			long* vec = choose_vector(method,&init_part,option1,option2);
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
			SetOptionsFromFile(&Options,"Mondriaan.defaults");
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
		printf("| \t avg: %5.2f\n",mean); fflush(stdout);
		MMDeleteSparseMatrix(&init_part);
		/*		sleep(1);*/
	}
	printf("average initials %5.2f\t average finals: %5.2f\n",ar_mean(initial_vec,outer_iter),ar_mean(outer_vec,outer_iter));
	MMDeleteSparseMatrix(&matrix);
	return 0;
}
