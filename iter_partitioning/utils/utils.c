#include "utils.h"


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
    long *pl;

    if (n==0){
        pl= NULL; 
    } else { 
        pl= (long *)malloc(n*SZLONG);
        if (pl==NULL) printf("vecallocl: not enough memory\n");
    }
    return pl;

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

void vecfreel(long *pl){
    /* This function frees a vector of longs */

    if (pl!=NULL)
        free(pl);

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

/*
* Printing methods used for debugging, self-explanatory
*/

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

/**********************************************************/


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

/*
* This function sorts all the items of J by increasing value val, using a counting sort.
* Stable: (items with the same value retain the original order)
* 0 <= J[i] <= maxval, for every i.
*/

long* CSortVec(long *J, long length, long maxval) {
  
    long t, j, r, total, tmp, *start, *C, *indices;

    /* initialization of the memory */
    
    C = vecallocl(length);
    start = vecallocl(maxval+1);
    indices = vecallocl(length);
    
    if (C == NULL || start == NULL) {
        fprintf(stderr, "CSortVec(): Not enough memory!\n");
        return FALSE;
    }

    /* emptying out the "buckets" vector */

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
	/*indexes[t]=start[j]; -- this to have the reverse permutation */
        start[j]++;
    }

    /* Third pass. Copy the items from C back into J. */
    for (t=0; t<length; t++){
      J[t]= C[t];
    }

    /* freeing memory */
    vecfreel(start);
    vecfreel(C);
    
    return indices;
}

/*
* Method that sorts the nonzeros of a struct sparsematrix such that the rows are in ascending order
*/

struct sparsematrixplus reorder_row_incr(struct sparsematrix* matrix){

    /* allocating memory */
    long length = matrix->NrNzElts;
    long* I = vecallocl(length);
    long* J = vecallocl(length);
    double* Val = vecallocd(length);

    int k,l;

    /* creating a temporary array for storing the values to be sorted (rows) */
    long* tempArray = vecallocl(length);
    for(k=0;k<length;k++) tempArray[k] = matrix->i[k];

    /* sorting tempArray with Counting Sort and getting back the permutation indices */
    long* indices = CSortVec(tempArray,length,matrix->m);

    /* creation of the vectors of the permuted rows, columns, value */
    for(l=0;l<length;l++){
      k = indices[l];
      I[l] = matrix->i[k];
      J[l] = matrix->j[k];
      Val[l] = matrix->ReValue[k];
    }

    /* creating the matrix part of the */
    struct sparsematrix newmatrix;
    MMSparseMatrixInit(&newmatrix);
    newmatrix.m = matrix->m;
    newmatrix.n = matrix->n;
    newmatrix.i = I;
    newmatrix.j = J;
    newmatrix.ReValue = Val;
    newmatrix.NrNzElts = length;

    /* removing the temporary array */
    vecfreel(tempArray);

    /* creating the final output */
    struct sparsematrixplus output;
    output.matrix = newmatrix;
    output.perm = indices;
    return output;
}

/*
 * methods that reorders the nonzeros of a given matrix such that the columns are in ascending order
 */
struct sparsematrixplus reorder_col_incr(struct sparsematrix* matrix){

    /* allocating memory */
    long length = matrix->NrNzElts;
    long* I = vecallocl(length);
    long* J = vecallocl(length);
    double* Val = vecallocd(length);

    int k,l;

    /* creating a temporary array for storing the values to be sorted (rows) */
    long* tempArray = vecallocl(length);
    for(k=0;k<length;k++) tempArray[k] = matrix->j[k];

    /* sorting tempArray with Counting Sort and getting back the permutation indices */
    long* indices = CSortVec(tempArray,length,matrix->n);

    /* creation of the vectors of the permuted rows, columns, value */
    for(l=0;l<length;l++){
      k = indices[l];
      I[l] = matrix->i[k];
      J[l] = matrix->j[k];
      Val[l] = matrix->ReValue[k];
    }

    /* creating the matrix part of the */
    struct sparsematrix newmatrix;
    MMSparseMatrixInit(&newmatrix);

    newmatrix.m = matrix->m;
    newmatrix.n = matrix->n;
    newmatrix.i = I;
    newmatrix.j = J;
    newmatrix.ReValue = Val;
    newmatrix.NrNzElts = length;

    /* removing the temporary array */
    vecfreel(tempArray);

    /* creating the final output */
    struct sparsematrixplus output;
    output.matrix = newmatrix;
    output.perm = indices;
    return output;
}

/*
* method that splits the two parts of A which have value "first"
* and value "second", assigning them respectively to Ar and Ac
*/
struct twomatrices split_matrix(struct sparsematrix* A, double first, double second){

  int k;

  /* initialization of the counters */
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
  for(k=0;k<(A->NrNzElts);k++){
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
  MMSparseMatrixInit(&A1);
  MMSparseMatrixInit(&A2); 
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

/*
* method that gets the indices of the first element of a given row for a matrix with incremental row
* i.e. gets the increment for the Incremental Row Storage
*/
long* get_increment_rows(struct sparsematrix* A){

  /* allocation of the memory */
  long* increment = vecallocl(A->m);
  int k,index = 0;
  
  /* first row is always pointed by first element */
  increment[0] = 0;

  /* loops that iterates through the list of nonzeros, registers row increment
  */
  for(k=0;k<A->NrNzElts;k++){
    if(A->i[k] != A->i[increment[index]]){
      index++;
      increment[index] = k;
    }
  }
  
  return increment;
}

/*
* method that gets the indices of the first element of a given column for a matrix with incremental columns
* i.e. gets the increment for the Incremental Column Storage
*/
long* get_increment_cols(struct sparsematrix* A){

  /* allocation of the memory */
  long* increment = vecallocl(A->n);
  int k,index = 0;
  
  /* first column is always pointed by first element */
  increment[0] = 0;

  /* loops that iterates through the list of nonzeros, registers column increment
  */
  for(k=0;k<A->NrNzElts;k++){
    if(A->j[k] != A->j[increment[index]]){
      index++;
      increment[index] = k;
    }
  }
  
  return increment;
}

/*
* method that updates the values of all elements in a particular row for a matrix stored with IRS.
*/
void update_rows(struct sparsematrix* A, long* increment_rows, int i, double value){
  int k = increment_rows[i];
  while(A->i[k] == i && k < A->NrNzElts){
    A->ReValue[k] = value;
    k++;
  }
}

/*
* method that updates the values of all elements in a particular column for a matrix stored with ICS.
*/
void update_cols(struct sparsematrix* A, long* increment_cols, int j, double value){
  /* requires matrix with ascending cols*/
  int k = increment_cols[j];
  while(A->j[k] == j && k < A->NrNzElts){
    A->ReValue[k] = value;
    k++;
  }
}

/*
* method that updates the values of all elements in a particular row for a matrix stored with ICS, using
* the fast access provided by the same matrix stored with IRS and a link between them.
*/
void update_rows_link(struct sparsematrix* A, struct sparsematrix* B, long* increment_rows, int i, double value, long* link){
  /* A = ascending rows, B = ascending columns */
  int k = increment_rows[i];
  while(A->i[k] == i && k < A->NrNzElts){
    B->ReValue[link[k]] = value;
    k++;
  }
}

/*
* method that updates the values of all elements in a particular column for a matrix stored with IRS, using
* the fast access provided by the same matrix stored with ICS and a link between them.
*/
void update_cols_link(struct sparsematrix* A, struct sparsematrix* B, long* increment_cols, int j, double value, long* link){
  /* A = ascending cols, B = ascending rows */
  int k = increment_cols[j];
  while(A->j[k] == j && k < A->NrNzElts){
    B->ReValue[link[k]] = value;
    k++;
  }
}

/*
* method that converts an array of doubles to an array of long
*/
long* double_array_to_long(double* input, int length){
    long* output = vecallocl(length);
    int i=0;
    for(i=0;i<length;i++)
        output[i] = (long)input[i];
    return output;
}

/*
 * method that creates a random permutation of 0,...,length
 */
long* random_permutation(long length){
  long* a = vecallocl(length);
  int i,j;
  long temp;
  for(i=0;i<length;i++) a[i]=i;
  for(i=0;i<length;i++){
    j = rand()%length;
    temp = a[j];
    a[j] = a[i];
    a[i] = temp;
  }
  return a;
}

/*
* method that returns a random integer in [0,bound]
*/
int randi(int bound){
  return ceil(rand()*1.0/RAND_MAX*bound);
}

/*
* adding xor functionality to C (which does not support operator overloading)
*/
int xor(int a, int b){
  return (!a && b) || (a && !b);
}

long* reverse_perm(long* input, int length){
    long* output = vecallocl(length);
    int i;
    for (i=0;i<length;i++)
        output[input[i]] = i;
    return output;
}
