#include <string.h>
#include <unistd.h>
#include <math.h>
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
	FILE* File;
	struct sparsematrix matrix;
	File = fopen(input, "r");
	if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
	fclose(File);

	srand(time(NULL));

	print_label_vector(method,option1,option2);

	int i;
	int outer_iter = 20;
	int inner_iter = 5;

	long* outer_vec = vecallocl(outer_iter);
	long* initial_vec = vecallocl(outer_iter);

	struct sparsematrix temp_matrix;
	for(i=0;i<outer_iter;i++){
		temp_matrix = copyMatrix(&matrix);
		struct sparsematrix init_part;
		initial_vec[i] = newMondriaan(&temp_matrix,8,&init_part);

		printf("%ld \t|\t",initial_vec[i]);fflush(stdout);	
		struct sparsematrixplus mplus = reorder_row_incr(&init_part);
		MMDeleteSparseMatrix(&init_part);
		init_part = mplus.matrix;
		vecfreel(mplus.perm);
		int k;

		long* inner_vec = vecallocl(inner_iter);
		for(k=0;k<inner_iter;k++){
			struct sparsematrix init2 = copyMatrix(&init_part);
			long* vec = choose_vector(method,&init_part,option1,option2);
			struct twomatrices one = overpaint(&init2,vec);
						struct sparsematrix B = createB(&(one.Ac),&(one.Ar));
			/*				copyHeader(&matrix,&B);
							B.MMTypeCode[0] = 'M';*/
							struct sparsematrix new_matrix;
							inner_vec[k] = newMondriaan(&B,5,&new_matrix);
							printf("%ld \t", inner_vec[k]); fflush(stdout);

							MMDeleteSparseMatrix(&new_matrix);
							MMDeleteSparseMatrix(&one.Ar);
							MMDeleteSparseMatrix(&one.Ac); 
							MMDeleteSparseMatrix(&init2);
			vecfreel(vec);
		}
		double mean = ar_mean(inner_vec,inner_iter);
		outer_vec[i]=mean;
		printf("| \t avg: %5.2f\n",mean); fflush(stdout);
		MMDeleteSparseMatrix(&init_part);
		vecfreel(inner_vec);
		/*		sleep(1);*/
	}
	printf("average initials %5d\t average finals: %5d\n",(int)ar_mean(initial_vec,outer_iter),(int)ar_mean(outer_vec,outer_iter));
	vecfreel(outer_vec);
	vecfreel(initial_vec);
	MMDeleteSparseMatrix(&matrix);
	return 0;
}
