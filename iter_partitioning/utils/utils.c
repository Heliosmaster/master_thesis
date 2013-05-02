#define SZINT (sizeof(int))
#define SZDBL (sizeof(double))
#define SZLONG (sizeof(long))

/* These functions can be used to allocate and deallocate vectors and matrices.
   If not enough memory available, one processor halts them all.
*/

double *vecallocd(int n){
    /* This function allocates a vector of doubles of length n */
    double *pd;

    if (n==0){
        pd= NULL;
    } else {
        pd= (double *)malloc(n*SZDBL);
        if (pd==NULL)
            printf("vecallocd: not enough memory\n");
    }
    return pd;

} /* end vecallocd */

int *vecalloci(int n){
    /* This function allocates a vector of integers of length n */
    int *pi;

    if (n==0){
        pi= NULL; 
    } else { 
        pi= (int *)malloc(n*SZINT);
        if (pi==NULL)
            printf("vecalloci: not enough memory\n");
    }
    return pi;

} /* end vecalloci */

long *vecallocl(int n){
    /* This function allocates a vector of longs of length n */
    long *pi;

    if (n==0){
        pi= NULL; 
    } else { 
        pi= (long *)malloc(n*SZLONG);
        if (pi==NULL)
            printf("vecalloci: not enough memory\n");
    }
    return pi;

} /* end vecalloci */

double **matallocd(int m, int n){
    /* This function allocates an m x n matrix of doubles */
    int i;
    double *pd, **ppd;

    if (m==0){
        ppd= NULL;  
    } else { 
        ppd= (double **)malloc(m*sizeof(double *));
        if (ppd==NULL)
            printf("matallocd: not enough memory\n");
        if (n==0){
            for (i=0; i<m; i++)
                ppd[i]= NULL;
        } else {  
            pd= (double *)malloc(m*n*SZDBL); 
            if (pd==NULL)
                printf("matallocd: not enough memory\n");
            ppd[0]=pd;
            for (i=1; i<m; i++)
                ppd[i]= ppd[i-1]+n;
        }
    }
    return ppd;

} /* end matallocd */

void vecfreed(double *pd){
    /* This function frees a vector of doubles */

    if (pd!=NULL)
        free(pd);

} /* end vecfreed */

void vecfreel(long *pd){
    /* This function frees a vector of longs */

    if (pd!=NULL)
        free(pd);

} /* end vecfreel */

void vecfreei(int *pi){
    /* This function frees a vector of integers */

    if (pi!=NULL)
        free(pi);

} /* end vecfreei */

void matfreed(double **ppd){
    /* This function frees a matrix of doubles */

    if (ppd!=NULL){
        if (ppd[0]!=NULL)
            free(ppd[0]);
        free(ppd);
    }

} /* end matfreed */

/**********************************************************/

struct twomatrices {
  struct sparsematrix Ar, Ac;
};

struct sparsematrixplus {
    struct sparsematrix matrix;
    long* perm;
};


/*
* methods to find out which rows/cols 
* (depending on whether the input vector is i or j)
* are empty / nonempty (and how many nonzeros they have)
*
* input = i/j
* NrNzElts = length(input)
* size = m/n
*/
long* nnz(long* input, int NrNzElts, int size){
  /* initialization of the output vector */
  long* nonz = vecallocl(size);

  /* filling out the vector with 0s (o/w MATLAB does not empty it) */
  int index;
  for(index=0;index<size;index++)
    nonz[index] = 0;

  /* sweep of the input vector: increased the counter for every index found */
  index = 0;
  while(index<NrNzElts){
    nonz[input[index]]++;
    index++;
  }
  return nonz;
}

long* CSortVec(long *J, long length, long maxval) {

    /* This function sorts the items J[lo..hi] by increasing value val,
       using a counting sort.
       Items with the same value retain the original order.
       maxval >= 0 is the maximum value that can occur;
       0 is the minimum value */

    long t, j, r, total, tmp, *start, *C, *indices;
    
    C = (long *)malloc(length*sizeof(long));
    start = (long *)malloc((maxval+1)*sizeof(long));
    indices = vecallocl(length);
    
    if (C == NULL || start == NULL) {
        fprintf(stderr, "CSortVec(): Not enough memory!\n");
        return FALSE;
    }

    for (r=0; r<=maxval; r++)
        start[r] = 0;

    /* First pass. Count the number of items for each value. */
    for (t=0; t<length; t++)
        start[J[t]]++;

    /* Make start cumulative */
    total = 0;
    for (r=0; r<=maxval; r++) {
        tmp = total;
        total += start[r];
        start[r] = tmp;
    }

    /* Second pass. Copy the items into C. */
    for (t=0; t<length; t++) {
        j = J[t];	
        C[start[j]]= j;
	indices[start[j]]=t;
	/*indexes[t]=start[j];*/
        start[j]++;
    }

    /* Third pass. Copy the items from C back into J. */
    for (t=0; t<length; t++)
        J[t]= C[t];

    free(start);
    free(C);
    
    return indices;
}

struct sparsematrixplus reorder_row_incr(struct sparsematrix* matrix){
    long length = matrix->NrNzElts;
    long* I = vecallocl(length);
    long* J = vecallocl(length);
    double* Val = vecallocd(length);

    int k,l;

    long* tempArray = vecallocl(length);
    for(k=0;k<length;k++) tempArray[k] = matrix->i[k];

    struct sparsematrix newmatrix;
    
    long* indices = CSortVec(tempArray,length,matrix->m);

    for(l=0;l<length;l++){
        k = indices[l];
	I[l] = matrix->i[k];
        J[l] = matrix->j[k];
        Val[l] = matrix->ReValue[k];

    }

    newmatrix.m = matrix->m;
    newmatrix.n = matrix->n;
    newmatrix.i = I;
    newmatrix.j = J;
    newmatrix.ReValue = Val;
    newmatrix.NrNzElts = length;
    vecfreel(tempArray);
    struct sparsematrixplus output;
    output.matrix = newmatrix;
    output.perm = indices;
    return output;
}

struct sparsematrixplus reorder_col_incr(struct sparsematrix* matrix){
    long length = matrix->NrNzElts;
    long* I = vecallocl(length);
    long* J = vecallocl(length);
    double* Val = vecallocd(length);

    int k,l;

    long* tempArray = vecallocl(length);
    for(k=0;k<length;k++) tempArray[k] = matrix->j[k];

    struct sparsematrix newmatrix;

    long* indices = CSortVec(tempArray,length,matrix->n);

    for(l=0;l<length;l++){
	k = indices[l];
        I[l] = matrix->i[k];
        J[l] = matrix->j[k];
        Val[l] = matrix->ReValue[k];

    }

    newmatrix.m = matrix->m;
    newmatrix.n = matrix->n;
    newmatrix.i = I;
    newmatrix.j = J;
    newmatrix.ReValue = Val;
    newmatrix.NrNzElts = length;
    
    vecfreel(tempArray);
    struct sparsematrixplus output;
    output.matrix = newmatrix;
    output.perm = indices;
    return output;
}



void print_matrix(struct sparsematrix matrix){
  int k;
  for(k=0;k<matrix.NrNzElts;k++)
    printf("(%ld,%ld)=%f\n", matrix.i[k]+1,matrix.j[k]+1,matrix.ReValue[k]);
}

void print_cplx_matrix(struct sparsematrix matrix){
  int k;
  for(k=0;k<matrix.NrNzElts;k++)
    printf("(%ld,%ld)=%f,%f\n", matrix.i[k]+1,matrix.j[k]+1,matrix.ReValue[k],matrix.ImValue[k]);
}

void print_vec(long* vec, int length){
  int i;
  for(i=0;i<length;i++)
    printf("%d: %ld",i+1,vec[i]);
}

void print_vec_inline(long* vec, int length){
  int i;
  for(i=0;i<length;i++)
    printf("%ld ",vec[i]);
  printf("\n");
}

void print_mat_to_file(char* name, struct sparsematrix matrix){
  FILE* File;
  File = fopen(name, "w");
  int k;
  for(k=0;k<matrix.NrNzElts;k++) fprintf(File,"%ld %ld - %f\n",matrix.i[k]+1,matrix.j[k]+1,matrix.ReValue[k]);
  fclose(File);
}

void print_vec_to_file(char* name, long* vec, int length){
  FILE* File;
  File = fopen(name, "a");
  int i;
  for(i=0;i<length;i++)
    fprintf(File,"%ld ",vec[i]);
  fprintf(File,"\n");
  fclose(File);
}

long* reverse_perm(long* input, int length){
    long* output = vecallocl(length);
    int i;
    for (i=0;i<length;i++)
        output[input[i]] = i;
    return output;
}


/*
* method that splits the two parts of A which have value "first"
* and value "second", assigning them respectively to Ar and Ac
*/
struct twomatrices split_matrix(struct sparsematrix* A, double first, double second){

  int k;

  int max1=0;
  int max2=0;

  /* initial sweep of the matrix to see how long should be the vectors*/
  for(k=0;k<A->NrNzElts;k++) 
    (A->ReValue[k] == second) ? max2++ : max1++;

  /* initialization of the vectors */
  long *i1 = vecallocl(max1);
  long *j1 = vecallocl(max1);
  double *v1 = vecallocd(max1);
  double *c1 = vecallocd(max1);

  long *i2 = vecallocl(max2);
  long *j2 = vecallocl(max2);
  double *v2 = vecallocd(max2);
  double *c2 = vecallocd(max2);

  /* population of the vectors */
  int index1=0;
  int index2=0;
  for(k=0;k<A->NrNzElts;k++){
    if (A->ReValue[k] == second ){
      i2[index2] = A->i[k];
      j2[index2] = A->j[k];
      v2[index2] = second;
      c2[index2] = 0.0;
      index2++;
    }
    else {
      i1[index1] = A->i[k];
      j1[index1] = A->j[k];
      v1[index1] = first;
      c1[index1] = 0.0;
      index1++;
    }
  }

  /* construction of the output */
  struct sparsematrix A1, A2;

  A1.m = A->m;
  A1.n = A->n;
  A1.NrNzElts = max1;
  A1.i = i1;
  A1.j = j1;
  A1.ReValue = v1;
  A1.ImValue = c1;

  A2.NrNzElts = max2;
  A2.m = A->m;
  A2.n = A->n;
  A2.i = i2;
  A2.j = j2;
  A2.ReValue = v2;
  A2.ImValue = c2;

  struct twomatrices output;
  output.Ar = A1;
  output.Ac = A2;

  return output;
}

void update_rows(struct sparsematrix* A, int i, double value/*, FILE* File*/){
  /* requires matrix with ascending rows */
  int k = 0;
  while(A->i[k] < i){
    k++;
  }
  while(A->i[k] == i){
    A->ReValue[k] = value;
    /*fprintf(File,"## (%ld,%ld)=%f\n",A->i[k]+1,A->j[k]+1,value); */
    k++;
  }
}

void update_cols(struct sparsematrix* A, int j, double value){
  /* requires matrix with ascending cols*/
  int k = 0;
  while(A->j[k] < j){
    k++;
  }
  while(A->j[k] == j){
    A->ReValue[k] = value;
    k++;
  }
}

void update_rows_link(struct sparsematrix* A, struct sparsematrix* B, int i, double value, long* link){
  /* A = ascending rows, B = ascending columns */
  int k = 0;
  while(A->i[k] < i){
    k++;
  }
  while(A->i[k] == i){
    B->ReValue[link[k]] = value;
    k++;
  }
}

void update_cols_link(struct sparsematrix* A, struct sparsematrix* B, int j, double value, long* link/*, FILE* File*/){
  /* A = ascending cols, B = ascending rows */
  int k = 0;
  while(A->j[k] < j){
    k++;
  }
  while(A->j[k] == j){
    B->ReValue[link[k]] = value;
    k++;
  }
}

long* double_array_to_long(double* input, int length){
    long* output = vecallocl(length);
    int i=0;
    for(i=0;i<length;i++)
        output[i] = (long)input[i];
    return output;
}
