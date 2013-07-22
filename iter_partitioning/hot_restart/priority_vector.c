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
	int i;
	long* vec;
	vecfreel(num_nnz);
	num_nnz = number_nonzeros(A);
	if(!widow){
		vec = indices;
	}	else{
		vec = vecallocl(m+n);
		int index_vec = 0;
		for(i=0;i<m+n;i++) if(num_nnz[indices[i]] != 1) vec[index_vec++] = indices[i];
		for(i=0;i<m+n;i++) if(num_nnz[indices[i]] == 1) vec[index_vec++] = indices[i];
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
		for(i=0;i<m+n;i++) if(num_nnz[indices[i]] != 1) vec[index_output++] = indices[i];
		for(i=0;i<m+n;i++) if(num_nnz[indices[i]] == 1) vec[index_output++] = indices[i];
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

/* splitstrategy = 0 => mix alternate, else mix spread */
long* po_unsorted_mix(struct sparsematrix* A, int splitstrategy){
	long* vec;
	long* rows = vecallocl(A->m);
	long* cols = vecallocl(A->n);
	int i;
	for(i=0;i<A->m;i++) rows[i] = i;
	for(i=0;i<A->n;i++) cols[i] = A->m+i;

	if(!splitstrategy){
		vec = mix_alternate(rows,A->m,cols,A->n);
	} else {
		vec = mix_spread(rows,A->m,cols,A->n);
	}
	vecfreel(rows);
	vecfreel(cols);
	return vec;

}

long* pa_unsorted_mix(struct sparsematrix* A, int splitstrategy){
	int cut_length, uncut_length;
	long *cut_part, *uncut_part;
	cut_and_uncut(A,&cut_part,&cut_length,&uncut_part,&uncut_length);
	int i;

	long* cut_rows = vecallocl(cut_length);
	long* cut_cols = vecallocl(cut_length);
	long* uncut_rows = vecallocl(uncut_length);
	long* uncut_cols = vecallocl(uncut_length);

	int index_cut_rows = 0, index_cut_cols = 0;
	for(i=0;i<cut_length;i++){
		if (cut_part[i]<A->m) cut_rows[index_cut_rows++] = cut_part[i];
		else cut_cols[index_cut_cols++] = cut_part[i];
	}
	int index_uncut_rows = 0, index_uncut_cols = 0;
	for(i=0;i<uncut_length;i++){
		if (uncut_part[i]<A->m){
			uncut_rows[index_uncut_rows++] = uncut_part[i];
		}
		else uncut_cols[index_uncut_cols++] = uncut_part[i];
	}

	long *cut, *uncut;

	if(!splitstrategy){
		cut = mix_alternate(cut_rows,index_cut_rows,cut_cols,cut_length-index_cut_rows);
		uncut = mix_alternate(uncut_rows,index_uncut_rows,uncut_cols,uncut_length-index_uncut_rows);
	} else {
		cut = mix_spread(cut_rows,index_cut_rows,cut_cols,cut_length-index_cut_rows);
		uncut = mix_spread(uncut_rows,index_uncut_rows,uncut_cols,uncut_length-index_uncut_rows);
	}
	long* output = vecallocl(A->m+A->n);
	for(i=0;i<cut_length;i++) output[i] = cut[i];
	for(i=0;i<uncut_length;i++) output[cut_length+i] = uncut[i];

	vecfreel(uncut);
	vecfreel(cut);
	vecfreel(cut_rows);
	vecfreel(uncut_rows);
	vecfreel(cut_cols);
	vecfreel(uncut_cols);
	vecfreel(cut_part);
	vecfreel(uncut_part);

	return output;
}

long* po_sorted_mix(struct sparsematrix* A, int splitstrategy, int widow){
	long* num_nnz = number_nonzeros(A);
	int m = A->m;
	int n = A->n;
	long* nnz_row = vecallocl(m);
	long* nnz_col = vecallocl(n);

	int i;
	for(i=0;i<m;i++) nnz_row[i] = num_nnz[i];
	for(i=0;i<n;i++) nnz_col[i] = num_nnz[m+i];


	long max_row = max_element(nnz_row,m);
	long max_col = max_element(nnz_col,n);
	long* indices_row = CSortVec(nnz_row,m,max_row);
	long* indices_col = CSortVec(nnz_col,n,max_col);
	long* vec;


	for(i=0;i<m;i++) nnz_row[i] = num_nnz[i];
	for(i=0;i<n;i++) nnz_col[i] = num_nnz[m+i];


	if(widow){
		long* tmp_row = vecallocl(m);
		long* tmp_col = vecallocl(n);
		int index_row = 0, index_col = 0;
		for(i=0;i<m;i++) if(nnz_row[indices_row[i]] != 1) tmp_row[index_row++] = indices_row[i];
		for(i=0;i<m;i++) if(nnz_row[indices_row[i]] == 1) tmp_row[index_row++] = indices_row[i];
		for(i=0;i<n;i++) if(nnz_col[indices_col[i]] != 1) tmp_col[index_col++] = indices_col[i];
		for(i=0;i<n;i++) if(nnz_col[indices_col[i]] == 1) tmp_col[index_col++] = indices_col[i];
		vecfreel(indices_row);
		vecfreel(indices_col);
		indices_row = tmp_row;
		indices_col = tmp_col;
	}

	for(i=0;i<n;i++) indices_col[i] += m;
	if(!splitstrategy) vec = mix_alternate(indices_row,m,indices_col,n);
	else	vec = mix_spread(indices_row,m,indices_col,n);

	vecfreel(num_nnz);
	vecfreel(nnz_row);
	vecfreel(nnz_col);
	vecfreel(indices_row);
	vecfreel(indices_col);
	return vec;
}

long* pa_sorted_mix(struct sparsematrix* A, int splitstrategy, int widow){
	long* num_nnz = number_nonzeros(A);
	int m = A->m;
	int n = A->n;
	int cut_length, uncut_length;
	long *cut_part, *uncut_part;
	cut_and_uncut(A,&cut_part,&cut_length,&uncut_part,&uncut_length);
	int i;
	long* cut_rows = vecallocl(cut_length);
	long* cut_cols = vecallocl(cut_length);
	long* uncut_rows = vecallocl(uncut_length);
	long* uncut_cols = vecallocl(uncut_length);

	int index_cut_rows = 0, index_cut_cols = 0;
	for(i=0;i<cut_length;i++){
		if (cut_part[i]<m) cut_rows[index_cut_rows++] = cut_part[i];
		else cut_cols[index_cut_cols++] = cut_part[i];
	}
	int index_uncut_rows = 0, index_uncut_cols = 0;
	for(i=0;i<uncut_length;i++){
		if (uncut_part[i]<m){
			uncut_rows[index_uncut_rows++] = uncut_part[i];
		}
		else uncut_cols[index_uncut_cols++] = uncut_part[i];
	}

	int length_cut_rows = index_cut_rows;
	int length_cut_cols = cut_length-length_cut_rows;
	int length_uncut_rows = index_uncut_rows;
	int length_uncut_cols = uncut_length-length_uncut_rows;

	long* nnz_cut_rows = vecallocl(length_cut_rows);
	long* nnz_cut_cols = vecallocl(length_cut_cols);
	long* nnz_uncut_rows = vecallocl(length_uncut_rows);
	long* nnz_uncut_cols = vecallocl(length_uncut_cols);

	for(i=0;i<length_cut_rows;i++) nnz_cut_rows[i] = num_nnz[cut_rows[i]];
	for(i=0;i<length_cut_cols;i++) nnz_cut_cols[i] = num_nnz[cut_cols[i]];
	for(i=0;i<length_uncut_rows;i++) nnz_uncut_rows[i] = num_nnz[uncut_rows[i]];
	for(i=0;i<length_uncut_cols;i++) nnz_uncut_cols[i] = num_nnz[uncut_cols[i]];

	long max_cut_rows = max_element(nnz_cut_rows,length_cut_rows);
	long max_cut_cols = max_element(nnz_cut_cols,length_cut_cols);
	long max_uncut_rows = max_element(nnz_uncut_rows,length_uncut_rows);
	long max_uncut_cols = max_element(nnz_uncut_cols,length_uncut_cols);

	long* indices_cut_rows = CSortVec(nnz_cut_rows,length_cut_rows,max_cut_rows);
	long* indices_cut_cols = CSortVec(nnz_cut_cols,length_cut_cols,max_cut_cols);
	long* indices_uncut_rows = CSortVec(nnz_uncut_rows,length_uncut_rows,max_uncut_rows);
	long* indices_uncut_cols = CSortVec(nnz_uncut_cols,length_uncut_cols,max_uncut_cols);
	for(i=0;i<length_cut_rows;i++) nnz_cut_rows[i] = num_nnz[cut_rows[i]];
	for(i=0;i<length_cut_cols;i++) nnz_cut_cols[i] = num_nnz[cut_cols[i]];
	for(i=0;i<length_uncut_rows;i++) nnz_uncut_rows[i] = num_nnz[uncut_rows[i]];
	for(i=0;i<length_uncut_cols;i++) nnz_uncut_cols[i] = num_nnz[uncut_cols[i]];


	if(widow){
		long* tmp_cut_rows = vecallocl(length_cut_rows);
		long* tmp_cut_cols = vecallocl(length_cut_cols);
		long* tmp_uncut_rows = vecallocl(length_uncut_rows);
		long* tmp_uncut_cols = vecallocl(length_uncut_cols);
		index_cut_rows = 0;
		index_cut_cols = 0;
		index_uncut_rows = 0;
		index_uncut_cols = 0;

		for(i=0;i<length_cut_rows;i++) if(nnz_cut_rows[indices_cut_rows[i]] != 1) tmp_cut_rows[index_cut_rows++] = indices_cut_rows[i];
		for(i=0;i<length_cut_rows;i++) if(nnz_cut_rows[indices_cut_rows[i]] == 1) tmp_cut_rows[index_cut_rows++] = indices_cut_rows[i];
		for(i=0;i<length_cut_cols;i++) if(nnz_cut_cols[indices_cut_cols[i]] != 1) tmp_cut_cols[index_cut_cols++] = indices_cut_cols[i];
		for(i=0;i<length_cut_cols;i++) if(nnz_cut_cols[indices_cut_cols[i]] == 1) tmp_cut_cols[index_cut_cols++] = indices_cut_cols[i];
		for(i=0;i<length_uncut_rows;i++) if(nnz_uncut_rows[indices_uncut_rows[i]] != 1) tmp_uncut_rows[index_uncut_rows++] = indices_uncut_rows[i];
		for(i=0;i<length_uncut_rows;i++) if(nnz_uncut_rows[indices_uncut_rows[i]] == 1) tmp_uncut_rows[index_uncut_rows++] = indices_uncut_rows[i];
		for(i=0;i<length_uncut_cols;i++) if(nnz_uncut_cols[indices_uncut_cols[i]] != 1) tmp_uncut_cols[index_uncut_cols++] = indices_uncut_cols[i];
		for(i=0;i<length_uncut_cols;i++) if(nnz_uncut_cols[indices_uncut_cols[i]] == 1) tmp_uncut_cols[index_uncut_cols++] = indices_uncut_cols[i];

		vecfreel(indices_cut_rows);
		vecfreel(indices_cut_cols);
		vecfreel(indices_uncut_rows);
		vecfreel(indices_uncut_cols);
		indices_cut_rows = tmp_cut_rows;
		indices_cut_cols = tmp_cut_cols;
		indices_uncut_rows = tmp_uncut_rows;
		indices_uncut_cols = tmp_uncut_cols;
	}

	long* sorted_cut_rows = vecallocl(length_cut_rows);
	long* sorted_cut_cols = vecallocl(length_cut_cols);
	long* sorted_uncut_rows = vecallocl(length_uncut_rows);
	long* sorted_uncut_cols = vecallocl(length_uncut_cols);

	for(i=0;i<length_cut_rows;i++) sorted_cut_rows[i] = cut_rows[indices_cut_rows[i]];
	for(i=0;i<length_cut_cols;i++) sorted_cut_cols[i] = cut_cols[indices_cut_cols[i]];
	for(i=0;i<length_uncut_rows;i++) sorted_uncut_rows[i] = uncut_rows[indices_uncut_rows[i]];
	for(i=0;i<length_uncut_cols;i++) sorted_uncut_cols[i] = uncut_cols[indices_uncut_cols[i]];
	long *cut, *uncut;

	if(!splitstrategy){
		cut = mix_alternate(sorted_cut_rows,length_cut_rows,sorted_cut_cols,length_cut_cols);
		uncut = mix_alternate(sorted_uncut_rows,length_uncut_rows,sorted_uncut_cols,length_uncut_cols);

	} else {
		cut = mix_spread(sorted_cut_rows,length_cut_rows,sorted_cut_cols,length_cut_cols);
		uncut = mix_spread(sorted_uncut_rows,length_uncut_rows,sorted_uncut_cols,length_uncut_cols);
	}

	long* output = vecallocl(m+n);
	for(i=0;i<cut_length;i++) output[i] = cut[i];
	for(i=0;i<uncut_length;i++) output[cut_length+i] = uncut[i];

	vecfreel(uncut);
	vecfreel(cut);
	vecfreel(cut_rows);
	vecfreel(uncut_rows);
	vecfreel(cut_cols);
	vecfreel(uncut_cols);
	vecfreel(cut_part);
	vecfreel(uncut_part);

	return output;

}
