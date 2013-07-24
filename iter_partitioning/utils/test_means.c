#include "utils.h"

int main(){

	/* initialization of a vector */
	long* vec = vecallocl(10);
	int i;
	for(i=0;i<5;i++) vec[i] = 1;
	for(i=5;i<10;i++) vec[i] = 2;

	/* printing it out unsorted */
	print_vec_inline(vec,10);
	printf("------------------\n");
	/* printing it out the sorting and the indices */
	
	printf("arithmetic mean: %f\n",ar_mean(vec,10));	
	printf("geometric mean: %f\n",geo_mean(vec,10));	
	vecfreel(vec);
	return 0;
}

