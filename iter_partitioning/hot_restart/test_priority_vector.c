#include "overpaint.h"
#include "priority_vector.h"

void cpvec(long* vec, int length){
	printf("%d\t",check_vector(vec,length)); 
	print_vec_inline(vec,length);
	vecfreel(vec);
}

int main(){

	/* reading the matrix from file */
	FILE* File;
	struct sparsematrix A;
	File = fopen("../../matrices/test_matrix.mtx", "r");
	/* File = fopen("../../matrices/tbdlinux.mtx", "r"); */
	if (!MMReadSparseMatrix(File, &A)) printf("Unable to read input matrix!\n");
	fclose(File);
	int m = A.m;
	int n = A.n;

	long* vec;
	printf("po_unsorted_concat:\n");
	vec = po_unsorted_concat(&A,0); cpvec(vec,m+n);
	vec = po_unsorted_concat(&A,1); cpvec(vec,m+n);
	printf("----\n");
	printf("pa_unsorted_concat:\n");
	vec = pa_unsorted_concat(&A,0); cpvec(vec,m+n);
	vec = pa_unsorted_concat(&A,1); cpvec(vec,m+n);
	printf("----\n");
	printf("po_unsorted_random:\n");
	vec = po_unsorted_random(&A); cpvec(vec,m+n);
	printf("----\n");
	printf("pa_unsorted_random:\n");
	vec = pa_unsorted_random(&A); cpvec(vec,m+n);
	printf("----\n");
	printf("po_unsorted_mix:\n");
	vec = po_unsorted_mix(&A,1); cpvec(vec,m+n);
	vec = po_unsorted_mix(&A,0); cpvec(vec,m+n);
	printf("----\n");
	printf("pa_unsorted_mix:\n");
	vec = pa_unsorted_mix(&A,1); cpvec(vec,m+n);
	vec = pa_unsorted_mix(&A,0); cpvec(vec,m+n);
	printf("----\n");
	printf("po_sorted_simple:\n");
	vec = po_sorted_simple(&A,0); cpvec(vec,m+n);
	vec = po_sorted_simple(&A,1); cpvec(vec,m+n);
	printf("----\n");
	printf("pa_sorted_simple:\n");
	vec = pa_sorted_simple(&A,0); cpvec(vec,m+n);
	vec = pa_sorted_simple(&A,1); cpvec(vec,m+n);
	printf("----\n");
	printf("po_sorted_mix:\n");
	vec = po_sorted_mix(&A,0,0); cpvec(vec,m+n);
	vec = po_sorted_mix(&A,1,0); cpvec(vec,m+n);
	vec = po_sorted_mix(&A,0,1); cpvec(vec,m+n);
	vec = po_sorted_mix(&A,1,1); cpvec(vec,m+n);
	printf("----\n");
	printf("pa_sorted_mix:\n");
	vec = pa_sorted_mix(&A,0,0); cpvec(vec,m+n);
	vec = pa_sorted_mix(&A,1,0); cpvec(vec,m+n);
	vec = pa_sorted_mix(&A,0,1); cpvec(vec,m+n);
	vec = pa_sorted_mix(&A,1,1); cpvec(vec,m+n);

	printf("----\n");


	MMDeleteSparseMatrix(&A);

	return 0;
}
