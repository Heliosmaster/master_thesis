#include "priority_vector.h"

long* choose_vector(int index, struct sparsematrix* A, int option1, int option2){
	switch(index){
		case 0:
			return po_unsorted_concat(A,option1);
		case 1:
			return pa_unsorted_concat(A,option1);
		case 2:
			return po_unsorted_random(A);
		case 3:
			return pa_unsorted_random(A);
		case 4:
			return po_unsorted_mix(A,option1);
		case 5:
			return pa_unsorted_mix(A,option1);
		case 6:
			return po_sorted_simple(A,option1);
		case 7:
			return pa_sorted_simple(A,option1);
		case 8:
			return po_sorted_concat(A,option1,option2);
		case 9:
			return pa_sorted_concat(A,option1,option2);
		case 10:
			return po_sorted_mix(A,option1,option2);
		case 11:
			return pa_sorted_mix(A,option1,option2);
		default:
			printf("Wrong index for priority vector\n");
			exit(1);
	}
}

void print_label_vector(int index,int option1, int option2){
	switch(index){
		case 0:
			printf("po_unsorted_concat %d:\n",option1);
			break;
		case 1:
			printf("pa_unsorted_concat %d:\n",option1);
			break;
		case 2:
			printf("po_unsorted_random:\n");
			break;
		case 3:
			printf("pa_unsorted_random:\n");
			break;
		case 4:
			printf("po_unsorted_mix %d:\n",option1);
			break;
		case 5:
			printf("pa_unsorted_mix %d:\n", option1);
			break;
		case 6:
			printf("po_sorted_simple %d:\n",option1);
			break;
		case 7:
			printf("pa_sorted_simple %d:\n",option1);
			break;
		case 8:
			printf("po_sorted_concat %d %d:\n",option1,option2);
			break;
		case 9:
			printf("pa_sorted_concat %d %d:\n",option1,option2);
			break;
		case 10:
			printf("po_sorted_mix %d %d:\n",option1,option2);
			break;
		case 11:
			printf("pa_sorted_mix %d %d:\n",option1,option2);
			break;
		default:
			printf("Wrong index for priority vector\n");
}
}
/*
 * function to retrieve the cut/uncut rows/column with their respective length.
 */
void get_pa_unsorted(struct sparsematrix* A, long** cut_rows, int* length_cut_rows, long** cut_cols, int* length_cut_cols, long** uncut_rows, int* length_uncut_rows, long** uncut_cols, int* length_uncut_cols){
	int cut_length, uncut_length;
	long *cut_part, *uncut_part;
	cut_and_uncut(A,&cut_part,&cut_length,&uncut_part,&uncut_length);
	int i;

	long* ct_rows = vecallocl(cut_length);
	long* ct_cols = vecallocl(cut_length);
	long* unct_rows = vecallocl(uncut_length);
	long* unct_cols = vecallocl(uncut_length);

	int index_cut_rows = 0, index_cut_cols = 0;
	for(i=0;i<cut_length;i++){
		if (cut_part[i]<A->m) ct_rows[index_cut_rows++] = cut_part[i];
		else ct_cols[index_cut_cols++] = cut_part[i];
	}
	int index_uncut_rows = 0, index_uncut_cols = 0;
	for(i=0;i<uncut_length;i++){
		if (uncut_part[i]<A->m)	unct_rows[index_uncut_rows++] = uncut_part[i];
		else unct_cols[index_uncut_cols++] = uncut_part[i];
	}

	*cut_rows = ct_rows;
	*cut_cols = ct_cols;
	*uncut_rows = unct_rows;
	*uncut_cols = unct_cols;

	*length_cut_rows = index_cut_rows;
	*length_cut_cols = cut_length-*length_cut_rows;
	*length_uncut_rows = index_uncut_rows;
	*length_uncut_cols = uncut_length-*length_uncut_rows;

	vecfreel(cut_part);
	vecfreel(uncut_part);
}

/*
 * function to retrieve the sorted cut/uncut rows/columns (with also the widow parameter).
 */
void get_pa_sorted(struct sparsematrix* A, int widow, long** sorted_cut_rows, int* length_cut_rows, long** sorted_cut_cols, int* length_cut_cols, long** sorted_uncut_rows, int* length_uncut_rows, long** sorted_uncut_cols, int* length_uncut_cols){
	long* num_nnz = number_nonzeros(A);
	int m = A->m, i;
	int cut_length, uncut_length;
	long *cut_part, *uncut_part;
	cut_and_uncut(A,&cut_part,&cut_length,&uncut_part,&uncut_length);
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
		if (uncut_part[i]<m)uncut_rows[index_uncut_rows++] = uncut_part[i];
		else uncut_cols[index_uncut_cols++] = uncut_part[i];
	}
	vecfreel(cut_part);
	vecfreel(uncut_part);

	*length_cut_rows = index_cut_rows;
	*length_cut_cols = cut_length-*length_cut_rows;
	*length_uncut_rows = index_uncut_rows;
	*length_uncut_cols = uncut_length-*length_uncut_rows;


	long* nnz_cut_rows;
	long max_cut_rows;
	long* indices_cut_rows;
	long* nnz_cut_cols;
	long max_cut_cols;
	long* indices_cut_cols;
	long* nnz_uncut_rows;
	long max_uncut_rows;
	long* indices_uncut_rows;
	long* nnz_uncut_cols;
	long max_uncut_cols;
	long* indices_uncut_cols;
	
	if(*length_cut_rows){
		nnz_cut_rows = vecallocl(*length_cut_rows);
		for(i=0;i<*length_cut_rows;i++) nnz_cut_rows[i] = num_nnz[cut_rows[i]];
		max_cut_rows = max_element(nnz_cut_rows,*length_cut_rows);
		indices_cut_rows = CSortVec(nnz_cut_rows,*length_cut_rows,max_cut_rows);
		for(i=0;i<*length_cut_rows;i++) nnz_cut_rows[i] = num_nnz[cut_rows[i]];

		if(widow){
			long* tmp_cut_rows = vecallocl(*length_cut_rows);
			index_cut_rows = 0;
			for(i=0;i<*length_cut_rows;i++) if(nnz_cut_rows[indices_cut_rows[i]] != 1) tmp_cut_rows[index_cut_rows++] = indices_cut_rows[i];
			for(i=0;i<*length_cut_rows;i++) if(nnz_cut_rows[indices_cut_rows[i]] == 1) tmp_cut_rows[index_cut_rows++] = indices_cut_rows[i];
			vecfreel(indices_cut_rows);
			indices_cut_rows = tmp_cut_rows;
		}
		vecfreel(nnz_cut_rows);
		*sorted_cut_rows = vecallocl(*length_cut_rows);
		long* srt_cut_rows = *sorted_cut_rows;
		for(i=0;i<*length_cut_rows;i++) srt_cut_rows[i] = cut_rows[indices_cut_rows[i]];
		vecfreel(cut_rows);
		vecfreel(indices_cut_rows);
	}

	if(*length_cut_cols){
		nnz_cut_cols = vecallocl(*length_cut_cols);
		for(i=0;i<*length_cut_cols;i++) nnz_cut_cols[i] = num_nnz[cut_cols[i]];
		max_cut_cols = max_element(nnz_cut_cols,*length_cut_cols);
		indices_cut_cols = CSortVec(nnz_cut_cols,*length_cut_cols,max_cut_cols);
		for(i=0;i<*length_cut_cols;i++) nnz_cut_cols[i] = num_nnz[cut_cols[i]];

		if(widow){
			long* tmp_cut_cols = vecallocl(*length_cut_cols);
			index_cut_cols = 0;
			for(i=0;i<*length_cut_cols;i++) if(nnz_cut_cols[indices_cut_cols[i]] != 1) tmp_cut_cols[index_cut_cols++] = indices_cut_cols[i];
			for(i=0;i<*length_cut_cols;i++) if(nnz_cut_cols[indices_cut_cols[i]] == 1) tmp_cut_cols[index_cut_cols++] = indices_cut_cols[i];
			vecfreel(indices_cut_cols);
			indices_cut_cols = tmp_cut_cols;
		}
		vecfreel(nnz_cut_cols);
		*sorted_cut_cols = vecallocl(*length_cut_cols);
		long* srt_cut_cols = *sorted_cut_cols;
		for(i=0;i<*length_cut_cols;i++) srt_cut_cols[i] = cut_cols[indices_cut_cols[i]];
		vecfreel(cut_cols);
		vecfreel(indices_cut_cols);
	}
	
		if(*length_uncut_rows){
		nnz_uncut_rows = vecallocl(*length_uncut_rows);
		for(i=0;i<*length_uncut_rows;i++) nnz_uncut_rows[i] = num_nnz[uncut_rows[i]];
		max_uncut_rows = max_element(nnz_uncut_rows,*length_uncut_rows);
		indices_uncut_rows = CSortVec(nnz_uncut_rows,*length_uncut_rows,max_uncut_rows);
		for(i=0;i<*length_uncut_rows;i++) nnz_uncut_rows[i] = num_nnz[uncut_rows[i]];

		if(widow){
			long* tmp_uncut_rows = vecallocl(*length_uncut_rows);
			index_uncut_rows = 0;
			for(i=0;i<*length_uncut_rows;i++) if(nnz_uncut_rows[indices_uncut_rows[i]] != 1) tmp_uncut_rows[index_uncut_rows++] = indices_uncut_rows[i];
			for(i=0;i<*length_uncut_rows;i++) if(nnz_uncut_rows[indices_uncut_rows[i]] == 1) tmp_uncut_rows[index_uncut_rows++] = indices_uncut_rows[i];
			vecfreel(indices_uncut_rows);
			indices_uncut_rows = tmp_uncut_rows;
		}
		vecfreel(nnz_uncut_rows);
		*sorted_uncut_rows = vecallocl(*length_uncut_rows);
		long* srt_uncut_rows = *sorted_uncut_rows;
		for(i=0;i<*length_uncut_rows;i++) srt_uncut_rows[i] = uncut_rows[indices_uncut_rows[i]];
		vecfreel(uncut_rows);
		vecfreel(indices_uncut_rows);
	}

	if(*length_uncut_cols){
		nnz_uncut_cols = vecallocl(*length_uncut_cols);
		for(i=0;i<*length_uncut_cols;i++) nnz_uncut_cols[i] = num_nnz[uncut_cols[i]];
		max_uncut_cols = max_element(nnz_uncut_cols,*length_uncut_cols);
		indices_uncut_cols = CSortVec(nnz_uncut_cols,*length_uncut_cols,max_uncut_cols);
		for(i=0;i<*length_uncut_cols;i++) nnz_uncut_cols[i] = num_nnz[uncut_cols[i]];

		if(widow){
			long* tmp_uncut_cols = vecallocl(*length_uncut_cols);
			index_uncut_cols = 0;
			for(i=0;i<*length_uncut_cols;i++) if(nnz_uncut_cols[indices_uncut_cols[i]] != 1) tmp_uncut_cols[index_uncut_cols++] = indices_uncut_cols[i];
			for(i=0;i<*length_uncut_cols;i++) if(nnz_uncut_cols[indices_uncut_cols[i]] == 1) tmp_uncut_cols[index_uncut_cols++] = indices_uncut_cols[i];
			vecfreel(indices_uncut_cols);
			indices_uncut_cols = tmp_uncut_cols;
		}
		vecfreel(nnz_uncut_cols);
		*sorted_uncut_cols = vecallocl(*length_uncut_cols);
		long* srt_uncut_cols = *sorted_uncut_cols;
		for(i=0;i<*length_uncut_cols;i++) srt_uncut_cols[i] = uncut_cols[indices_uncut_cols[i]];
		vecfreel(uncut_cols);
		vecfreel(indices_uncut_cols);
	}
	
	vecfreel(num_nnz);
}

/*
 * function to get the sorted rows/columns (according to widow parameter)
 */
void get_po_sorted(struct sparsematrix* A, int widow, long** sorted_rows, long** sorted_cols){
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

	for(i=0;i<m;i++) nnz_row[i] = num_nnz[i];
	for(i=0;i<n;i++) nnz_col[i] = num_nnz[m+i];
	vecfreel(num_nnz);

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
	vecfreel(nnz_row);
	vecfreel(nnz_col);

	for(i=0;i<n;i++) indices_col[i] += m;

	*sorted_rows = indices_row;
	*sorted_cols = indices_col;
}


/*
 * computes a vector that is simply [rows, columns] (if flag=0), or [columns,rows] (flag=1)
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
 * computes a vector that is [cut_rows,cut_cols,uncut_rows,uncut_cols) (flag=0) or [cut_cols,cut_rows,uncut_cols,uncut_rows] (flag=1)
 */
long* pa_unsorted_concat(struct sparsematrix* A, int flag){
	int i;
	int m = A->m;
	int n = A->n;
	int cut_length, uncut_length;
	long *cut_part, *uncut_part;

	cut_and_uncut(A,&cut_part,&cut_length,&uncut_part,&uncut_length);

	if(flag){
		reverse_vector(&cut_part,cut_length);
		reverse_vector(&uncut_part,uncut_length);
	}

	long* vec = vecallocl(m+n);
	for(i=0;i<uncut_length;i++) vec[cut_length+i] = uncut_part[i];
	for(i=0;i<cut_length;i++) vec[i] = cut_part[i];

		vecfreel(cut_part);
	vecfreel(uncut_part);

	return vec;
}

/*
 * computes a vector that is just the random permutation of the rows/columns indices
 */
long* po_unsorted_random(struct sparsematrix* A){
	return random_permutation(A->m+A->n);
}

/*
 * computes a vector that is [uncut,cut] and each part is randomly permuted
 */
long* pa_unsorted_random(struct sparsematrix* A){
	int i;
	int cut_length, uncut_length;
	long *cut_part, *uncut_part;

	cut_and_uncut(A,&cut_part,&cut_length,&uncut_part,&uncut_length);

	long* cut_perm = random_permutation(cut_length);
	long* uncut_perm = random_permutation(uncut_length);

	int m = A->m, n=A->n;
	long* vec = vecallocl(m+n);
	int index_vec = 0;

	for(i=0;i<uncut_length;i++) vec[index_vec++] = uncut_part[uncut_perm[i]];
	for(i=0;i<cut_length;i++) vec[index_vec++] = cut_part[cut_perm[i]];

	vecfreel(cut_part);
	vecfreel(cut_perm);
	vecfreel(uncut_part);
	vecfreel(uncut_perm);
	return vec;
}

/*
 * computes a vector with indices sorted by increasing number of nonzeros (and widow parameter)
 */
long* po_sorted_simple(struct sparsematrix* A, int widow){
	long* num_nnz = number_nonzeros(A);
	int m = A->m;
	int n = A->n;
	long max = max_element(num_nnz,m+n);
	int i;

	long* indices = CSortVec(num_nnz,m+n,max);
	long* vec;
	vecfreel(num_nnz);
	num_nnz = number_nonzeros(A);
	if(!widow) vec = indices;
	else{
		vec = vecallocl(m+n);
		int index_vec = 0;
		for(i=0;i<m+n;i++) if(num_nnz[indices[i]] != 1) vec[index_vec++] = indices[i];
		for(i=0;i<m+n;i++) if(num_nnz[indices[i]] == 1) vec[index_vec++] = indices[i];
		vecfreel(indices);
	}
	vecfreel(num_nnz);
	return vec;
}

/*
 * computes a vector [uncut,cut] in which each part is sorted by increasing number of nonzeros (with widow parameter)
 */
long* pa_sorted_simple(struct sparsematrix* A, int widow){
	int i;
	int cut_length, uncut_length;
	long *cut_part, *uncut_part;

	cut_and_uncut(A,&cut_part,&cut_length,&uncut_part,&uncut_length);
	long* num_nnz = number_nonzeros(A);
	int m = A->m;
	int n = A->n;

	long* nz_cut;
	long max_cut;
	long* indices_cut;

	long* nz_uncut;
	long max_uncut;
	long* indices_uncut;

	if(cut_length){
		nz_cut = vecallocl(cut_length);
		for(i=0;i<cut_length;i++) nz_cut[i] = num_nnz[cut_part[i]];
		max_cut = max_element(nz_cut,cut_length);
		indices_cut = CSortVec(nz_cut,cut_length,max_cut);
		for(i=0;i<cut_length;i++) nz_cut[i] = num_nnz[cut_part[i]];

		if(widow) {
			long* tmp_cut = vecallocl(cut_length);
			int index_cut = 0;
			for(i=0;i<cut_length;i++) if (nz_cut[indices_cut[i]] != 1) tmp_cut[index_cut++] = indices_cut[i];
			for(i=0;i<cut_length;i++) if (nz_cut[indices_cut[i]] == 1) tmp_cut[index_cut++] = indices_cut[i];
			vecfreel(indices_cut);
			indices_cut = tmp_cut;
		}
	}

	if(uncut_length){
		nz_uncut = vecallocl(uncut_length);
		for(i=0;i<uncut_length;i++) nz_uncut[i] = num_nnz[uncut_part[i]];
		max_uncut = max_element(nz_uncut,uncut_length);
		indices_uncut = CSortVec(nz_uncut,uncut_length,max_uncut);
		for(i=0;i<uncut_length;i++) nz_uncut[i] = num_nnz[uncut_part[i]];
		if(widow){
			long* tmp_uncut = vecallocl(uncut_length);
			int index_uncut = 0;
			for(i=0;i<uncut_length;i++) if (nz_uncut[indices_uncut[i]] != 1) tmp_uncut[index_uncut++] = indices_uncut[i];
			for(i=0;i<uncut_length;i++) if (nz_uncut[indices_uncut[i]] == 1) tmp_uncut[index_uncut++] = indices_uncut[i];
			vecfreel(indices_uncut);
			indices_uncut = tmp_uncut;
		}
	}

	long* vec = vecallocl(m+n);
	int index_vec = 0;
	for(i=0;i<uncut_length;i++) vec[index_vec++] = uncut_part[indices_uncut[i]];
	for(i=0;i<cut_length;i++) vec[index_vec++] = cut_part[indices_cut[i]];

	if(cut_length){
		vecfreel(cut_part);
		vecfreel(nz_cut);
		vecfreel(indices_cut);
	}
	if(uncut_length) {
		vecfreel(uncut_part);
		vecfreel(nz_uncut);
		vecfreel(indices_uncut);
	vecfreel(num_nnz);
	}
	return vec;
}

/*
 * computes a vector in which rows and column are mixed (alternatively with splitstrategy=0, spread otherwise)
 */
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

/*
 * computes a vector [uncut,cut] in which each part has rows and column mixed
 */
long* pa_unsorted_mix(struct sparsematrix* A, int splitstrategy){

	long* cut_rows, *cut_cols, *uncut_rows, *uncut_cols;
	int length_cut_rows, length_cut_cols, length_uncut_rows, length_uncut_cols;	
	get_pa_unsorted(A,&cut_rows,&length_cut_rows,&cut_cols,&length_cut_cols,&uncut_rows,&length_uncut_rows,&uncut_cols,&length_uncut_cols);

	long *cut, *uncut;

	if(length_cut_rows == 0){
		cut = cut_cols;
	} else if (length_cut_cols == 0) {
		cut = cut_rows;
	} else if(!splitstrategy) {
		cut = mix_alternate(cut_rows,length_cut_rows,cut_cols,length_cut_cols);
	} else {
		cut = mix_spread(cut_rows,length_cut_rows,cut_cols,length_cut_cols);
	}

	if(length_uncut_rows == 0){
		uncut = uncut_cols;
	} else if (length_uncut_cols == 0) {
		uncut = uncut_rows;
	} else if(!splitstrategy) {
		uncut = mix_alternate(uncut_rows,length_uncut_rows,uncut_cols,length_uncut_cols);
	} else {
		uncut = mix_spread(uncut_rows,length_uncut_rows,uncut_cols,length_uncut_cols);
	}

	int i;

	long* vec = vecallocl(A->m+A->n);
	int index_vec = 0;

	for(i=0;i<length_uncut_rows+length_uncut_cols;i++) vec[index_vec++] = uncut[i];
	for(i=0;i<length_cut_rows+length_cut_cols;i++) vec[index_vec++] = cut[i];

	if(length_cut_rows)	vecfreel(cut_rows);
	if(length_cut_cols)	vecfreel(cut_cols);
	if(length_uncut_rows)	vecfreel(uncut_rows);
	if(length_uncut_cols)	vecfreel(uncut_cols);


	if(length_uncut_rows && length_uncut_cols) vecfreel(uncut);
	if(length_cut_rows && length_cut_cols) vecfreel(cut);
	return vec;
}

/*
 * computes a vector in which rows and columns are sorted (with widow param) and mixed
 */
long* po_sorted_mix(struct sparsematrix* A, int splitstrategy, int widow){
	long* sorted_rows, *sorted_cols;
	get_po_sorted(A,widow,&sorted_rows,&sorted_cols);

	int m = A->m, n = A->n;

	long* vec;
	if(!splitstrategy) vec = mix_alternate(sorted_rows,m,sorted_cols,n);
	else	vec = mix_spread(sorted_rows,m,sorted_cols,n);

	vecfreel(sorted_rows);
	vecfreel(sorted_cols);

	return vec;
}

/* 
 * computes a vector [uncut,cut] in which rows and columns are first sorted (independently) and then mixed
 */
long* pa_sorted_mix(struct sparsematrix* A, int splitstrategy, int widow){
	long* sorted_cut_rows, *sorted_cut_cols, *sorted_uncut_rows, *sorted_uncut_cols;
	int length_cut_rows, length_cut_cols, length_uncut_rows, length_uncut_cols;

	get_pa_sorted(A,widow,&sorted_cut_rows,&length_cut_rows,&sorted_cut_cols,&length_cut_cols,&sorted_uncut_rows,&length_uncut_rows,&sorted_uncut_cols,&length_uncut_cols);

	int i;
	int cut_length = length_cut_rows+length_cut_cols;
	int uncut_length = length_uncut_rows + length_uncut_cols;


	long *cut, *uncut;

	if(!length_cut_rows){
		cut = sorted_cut_cols;
	} else if (!length_cut_cols) {
		cut = sorted_cut_rows;
	} else if(!splitstrategy) {
		cut = mix_alternate(sorted_cut_rows,length_cut_rows,sorted_cut_cols,length_cut_cols);
	} else {
		cut = mix_spread(sorted_cut_rows,length_cut_rows,sorted_cut_cols,length_cut_cols);
	}

	if(!length_uncut_rows){
		uncut = sorted_uncut_cols;
	} else if (!length_uncut_cols) {
		uncut = sorted_uncut_rows;
	} else if(!splitstrategy) {
		uncut = mix_alternate(sorted_uncut_rows,length_uncut_rows,sorted_uncut_cols,length_uncut_cols);
	} else {
		uncut = mix_spread(sorted_uncut_rows,length_uncut_rows,sorted_uncut_cols,length_uncut_cols);
	}

	long* vec = vecallocl(A->m+A->n);
	int index_vec = 0;


	for(i=0;i<uncut_length;i++) vec[index_vec++] = uncut[i];
	for(i=0;i<cut_length;i++) vec[index_vec++] = cut[i];

	if(length_cut_rows)	vecfreel(sorted_cut_rows);
	if(length_cut_cols)	vecfreel(sorted_cut_cols);
	if(length_uncut_rows)	vecfreel(sorted_uncut_rows);
	if(length_uncut_cols)	vecfreel(sorted_uncut_cols);


	if(length_uncut_rows && length_uncut_cols) vecfreel(uncut);
	if(length_cut_rows && length_cut_cols) vecfreel(cut);
	return vec;
}

/*
 * computes a vector in which rows and columns are sorted independently and then put consecutively
 */
long* po_sorted_concat(struct sparsematrix* A, int widow, int flag){
	long* sorted_rows, *sorted_cols;

	get_po_sorted(A,widow,&sorted_rows,&sorted_cols);
	int i, m = A->m, n = A->n;
	long* vec = vecallocl(m+n);
	int index_vec = 0;
	if(!flag){
		/* rows before cols */
		for(i=0;i<m;i++) vec[index_vec++] = sorted_rows[i];
		for(i=0;i<n;i++) vec[index_vec++] = sorted_cols[i];
	} else {
		/* cols before rows */
		for(i=0;i<n;i++) vec[index_vec++] = sorted_cols[i];
		for(i=0;i<m;i++) vec[index_vec++] = sorted_rows[i];
	}

	vecfreel(sorted_rows);
	vecfreel(sorted_cols);
	return vec;
}

/*
 * computes a vector in which cut/uncut rows/columns are sorted independently and then put consecutively according to flag
 */
long* pa_sorted_concat(struct sparsematrix *A, int widow, int flag){
	long* sorted_cut_rows, *sorted_cut_cols, *sorted_uncut_rows, *sorted_uncut_cols;
	int length_cut_rows, length_cut_cols, length_uncut_rows, length_uncut_cols;
	get_pa_sorted(A,widow,&sorted_cut_rows,&length_cut_rows,&sorted_cut_cols,&length_cut_cols,&sorted_uncut_rows,&length_uncut_rows,&sorted_uncut_cols,&length_uncut_cols);

	int i;
	int cut_length = length_cut_rows+length_cut_cols;
	int uncut_length = length_uncut_rows + length_uncut_cols;
	long *cut = vecallocl(cut_length);
	long *uncut = vecallocl(uncut_length);
	int	index_cut = 0, index_uncut = 0;
	if(!flag) {
		/* rows before cols */
		for(i=0;i<length_cut_rows;i++) cut[index_cut++] = sorted_cut_rows[i];
		for(i=0;i<length_cut_cols;i++) cut[index_cut++] = sorted_cut_cols[i];
		for(i=0;i<length_uncut_rows;i++) uncut[index_uncut++] = sorted_uncut_rows[i];
		for(i=0;i<length_uncut_cols;i++) uncut[index_uncut++] = sorted_uncut_cols[i];
	} else {
		/* cols before rows */
		for(i=0;i<length_cut_cols;i++) cut[index_cut++] = sorted_cut_cols[i];
		for(i=0;i<length_cut_rows;i++) cut[index_cut++] = sorted_cut_rows[i];
		for(i=0;i<length_uncut_cols;i++) uncut[index_uncut++] = sorted_uncut_cols[i];
		for(i=0;i<length_uncut_rows;i++) uncut[index_uncut++] = sorted_uncut_rows[i];
	}

	if(length_cut_rows) vecfreel(sorted_cut_rows);
	if(length_cut_cols) vecfreel(sorted_cut_cols);
	if(length_uncut_rows) vecfreel(sorted_uncut_rows);
	if(length_uncut_cols) vecfreel(sorted_uncut_cols);

	long* vec = vecallocl(A->m+A->n);
	for(i=0;i<cut_length;i++) vec[i] = cut[i];
	for(i=0;i<uncut_length;i++) vec[cut_length+i] = uncut[i];

	vecfreel(uncut);
	vecfreel(cut);
	return vec;
}
