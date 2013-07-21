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
	vec = po_unsorted_concat(&A,0); cpvec(vec,m+n);
	vec = po_unsorted_concat(&A,1); cpvec(vec,m+n);
	printf("----\n");
	vec = pa_unsorted_concat(&A,0); cpvec(vec,m+n);
	vec = pa_unsorted_concat(&A,1); cpvec(vec,m+n);
	printf("----\n");
	vec = po_unsorted_random(&A); cpvec(vec,m+n);
	printf("----\n");
	vec = pa_unsorted_random(&A); cpvec(vec,m+n);
	printf("----\n");
	vec = po_sorted_simple(&A,0); cpvec(vec,m+n);
	vec = po_sorted_simple(&A,1); cpvec(vec,m+n);
	printf("----\n");
	vec = pa_sorted_simple(&A,0); cpvec(vec,m+n);
	vec = pa_sorted_simple(&A,1); cpvec(vec,m+n);
	
	MMDeleteSparseMatrix(&A);
	
	return 0;
}
