#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <Mondriaan.h>
#include "utils.c"

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
	printf("CSort\n");
	/* sorting it with Counting Sort and retrieving indices */
	long* indices = CSortVec(vec,10,8);

	/* printing it out the sorting and the indices */
	print_vec_inline(vec,10);
	print_vec_inline(indices,10);
	printf("------------------\n");
	printf("QSort\n");

	/* restoring the unsorted order */
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

	/* sorting it with Quick Sort and retrieving indices */
	long* indices2 = QSort(vec,10);

	/* printing it out the sorting and the indices */
	print_vec_inline(vec,10);
	print_vec_inline(indices2,10);
	
	vecfreel(vec);
	vecfreel(indices);
	vecfreel(indices2);
}

