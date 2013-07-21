#include "priority_vector.h"

/*
 * flag = 0 => row, else column
 */
long* po_unsorted_concat(struct sparsematrix* A, int flag){
	int i;
	int m = A->m;
	int n = A->n;

	long* vec = vecallocl(m+n);
	if(!flag)	for(i=0;i<m+n;i++) vec[i] = i;
	else for(i=0;i<m+n;i++) vec[i]=m+n-i-1;
	return vec;
}

/*
 * flag=0 => row (ascending order sort), else column (descending order sort)
 */
long* pa_unsorted_concat(struct sparsematrix* A, int flag){
	int i;
	int m = A->m;
	int n = A->n;
	int cut_length, uncut_length;
	long *cut_part, *uncut_part;

	cut_and_uncut(A,&cut_part,&cut_length,&uncut_part,&uncut_length);
	long* vec = vecallocl(m+n);
	if(flag){
		reverse_vector(&cut_part,cut_length);
		reverse_vector(&uncut_part,uncut_length);
	}
	for(i=0;i<cut_length;i++) vec[i] = cut_part[i];
	for(i=0;i<uncut_length;i++) vec[cut_length+i] = uncut_part[i];

	vecfreel(cut_part);
	vecfreel(uncut_part);

	return vec;
}

long* po_unsorted_random(struct sparsematrix* A){
	return random_permutation(A->m+A->n);
}

long* pa_unsorted_random(struct sparsematrix* A){
	int i;
	int cut_length, uncut_length;
	long *cut_part, *uncut_part;

	cut_and_uncut(A,&cut_part,&cut_length,&uncut_part,&uncut_length);

	long* cut_perm = random_permutation(cut_length);
	long* uncut_perm = random_permutation(uncut_length);

	int m = A->m, n=A->n;
	long* vec = vecallocl(m+n);
	
	for(i=0;i<cut_length;i++) vec[i] = cut_part[cut_perm[i]];
	for(i=0;i<uncut_length;i++) vec[cut_length+i] = uncut_part[uncut_perm[i]];

	vecfreel(cut_part);
	vecfreel(cut_perm);
	vecfreel(uncut_part);
	vecfreel(uncut_perm);
	return vec;
}

long* po_sorted_simple(struct sparsematrix* A,int widow){
	long* num_nnz = number_nonzeros(A);
	int m = A->m;
	int n = A->n;
	long max = max_element(num_nnz,m+n);

	long* indices = CSortVec(num_nnz,m+n,max);

	long* vec;

	if(!widow){
		vec = indices;
	}	else{
		vec = vecallocl(m+n);
		int i, index_vec = 0;
		for(i=0;i<m+n;i++) if(indices[i] != 1) vec[index_vec++] = indices[i];
		for(i=0;i<m+n;i++) if(indices[i] == 1) vec[index_vec++] = indices[i];
		vecfreel(indices);
	}
	vecfreel(num_nnz);
	return vec;
}

long* pa_sorted_simple(struct sparsematrix* A, int widow){
	int i;
	int cut_length, uncut_length;
	long *cut_part, *uncut_part;

	cut_and_uncut(A,&cut_part,&cut_length,&uncut_part,&uncut_length);
	
	long* num_nnz = number_nonzeros(A);
	int m = A->m;
	int n = A->n;

	long* nz_cut = vecallocl(cut_length);
	long* nz_uncut = vecallocl(uncut_length);

	int index_cut = 0, index_uncut = 0;
	for(i=0;i<cut_length;i++) nz_cut[index_cut++] = num_nnz[cut_part[i]];
	for(i=0;i<uncut_length;i++) nz_uncut[index_uncut++] = num_nnz[uncut_part[i]];


	long max_cut = max_element(nz_cut,cut_length);
	long max_uncut = max_element(nz_uncut,uncut_length);

	long* indices_cut_sort = CSortVec(nz_cut,cut_length,max_cut);
	long* indices_uncut_sort = CSortVec(nz_uncut,uncut_length,max_uncut);

	long* indices = vecallocl(m+n);
	for(i=0;i<cut_length;i++) indices[i] = cut_part[indices_cut_sort[i]];
	for(i=0;i<uncut_length;i++) indices[cut_length+i] = uncut_part[indices_uncut_sort[i]];
	
	long* vec;
	if(!widow){
		vec = indices;
	}	else {
		vec = vecallocl(m+n);
		int index_output = 0;
		for(i=0;i<m+n;i++) if(indices[i] != 1) vec[index_output++] = indices[i];
		for(i=0;i<m+n;i++) if(indices[i] == 1) vec[index_output++] = indices[i];
		vecfreel(indices);
	}
	vecfreel(cut_part);
	vecfreel(uncut_part);
	vecfreel(nz_cut);
	vecfreel(nz_uncut);
	vecfreel(indices_cut_sort);
	vecfreel(indices_uncut_sort);
	vecfreel(num_nnz);
	return vec;
}
