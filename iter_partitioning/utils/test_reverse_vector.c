#include "utils.h"

int main(){

	/* initialization of a vector */
	long* vec = vecallocl(10);
	vec[0] = 7;
	vec[1] = 3;
	vec[2] = 2;
	vec[3] = 7;
	vec[4] = 1;
	vec[5] = 6;
	vec[6] = 6;
	vec[7] = 5;
	vec[8] = 4;
	vec[9] = 8;

	/* printing it out unsorted */
	print_vec_inline(vec,10);
	printf("------------------\n");
	/* printing it out the sorting and the indices */
	reverse_vector(&vec,10);
	print_vec_inline(vec,10);	
	vecfreel(vec);
	return 0;
}

