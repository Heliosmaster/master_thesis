#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <Mondriaan.h>
#include "utils.c"

struct TwoParts {
  struct sparsematrix Ar, Ac;
};

void print_matrix(struct sparsematrix matrix){
  int k;
  for(k=0;k<matrix.NrNzElts;k++) printf("(%ld,%ld)=%f\n", matrix.i[k]+1,matrix.j[k]+1,matrix.ReValue[k]);
}

void print_vectorl(long* vec, int length){
  int i;
  for(i=0;i<length;i++)
    printf("%d: %ld",i+1,vec[i]);
}

void print_vec2(long* vec, int length){
  int i;
  for(i=0;i<length;i++)
    printf("%ld ",vec[i]);
  printf("\n");
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

/*
* method that splits the two parts of A which have value 1
* and value two
*/
struct TwoParts split1and2(struct sparsematrix A){

  int k;
  struct TwoParts output;

  struct sparsematrix A1, A2;

  int max1=0;
  int max2=0;

  // initial sweep of the matrix to see how long should be the vectors
  for(k=0;k<A.NrNzElts;k++) (A.ReValue[k] == 2.0) ? max2++ : max1++;

  //initialization of the vectors
  long *i1 = vecallocl(max1);
  long *j1 = vecallocl(max1);
  double *v1 = vecallocd(max1);
  long *i2 = vecallocl(max2);
  long *j2 = vecallocl(max2);
  double *v2 = vecallocd(max2);

  // indices to populate i and j
  int index1=0;
  int index2=0;
  for(k=0;k<A.NrNzElts;k++){
    if (A.ReValue[k] == 2.0 ){
      i2[index2] = A.i[k];
      j2[index2] = A.j[k];
      v2[index2] = 2.0;
      index2++;
    }
    else {
      i1[index1] = A.i[k];
      j1[index1] = A.j[k];
      v1[index1] = 1.0;
      index1++;
    }
  }

  A1.m = A.m;
  A2.m = A.m;

  A1.n = A.n;
  A2.n = A.n;
  
  A1.NrNzElts = max1;
  A2.NrNzElts = max2;

  A1.i = i1;
  A1.j = j1;

  A2.i = i2;
  A2.j = j2;

  A1.ReValue = v1;
  A2.ReValue = v2;

  output.Ar = A1;
  output.Ac = A2;

  return output;
}

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
  int index = 0;
  long* nonz = vecallocl(size);
  while(index<NrNzElts){
    nonz[input[index]]++;
    index++;
  }
  return nonz;
}

/*
* function that assigns the nonzeros of matrix either to Ar or Ac
*/
struct TwoParts localview(struct sparsematrix matrix){

  // dividing between A1 and A2
  struct TwoParts A = split1and2(matrix);
  struct sparsematrix A1 = A.Ar;
  struct sparsematrix A2 = A.Ac;

  int m = matrix.m;
  int n = matrix.n;

  /* 
  * building the bookkeeping vectors
  * nzXr = nonzeros in the rows of AX
  * nzXc = nonzeros in the columns of AX
  * nzr,nzc = nonzeros in row/col of matrix
  */
  long* nz1r = nnz(A1.i, A1.NrNzElts, A1.m);
  long* nz2r = nnz(A2.i, A2.NrNzElts, A2.m);
  long* nzr = nnz(matrix.i, matrix.NrNzElts, matrix.m);

  long* nz1c = nnz(A1.j, A1.NrNzElts, A1.n);
  long* nz2c = nnz(A2.j, A2.NrNzElts, A2.n);
  long* nzc = nnz(matrix.j, matrix.NrNzElts, matrix.n);

  // storing the number of nonzeros that have to be assigned
  int len = matrix.NrNzElts;

  /* 
  * initialization of the new vectors to be populated
  * assuming everything is assigned to one and the other stays empty
  * the max size is matrix.NrNzElts (len)
  */
  long* ir = vecallocl(len);
  long* jr = vecallocl(len);
  long* ic = vecallocl(len);
  long* jc = vecallocl(len);

  // counters for filling of ir,jr and ic,jc
  int index_r = 0;
  int index_c = 0;
  
  int i,j,k;
  k = 0;
  while(len>0){

    // k randomly chosen between 0 and len
    k = randi(len);

    // computing explicitly row and column of the k-th element of the matrix
    i = matrix.i[k];
    j = matrix.j[k];
  
    // computing whether i,j are split
    int rowsplit = (nz1r[i] && nz2r[i]);
    int colsplit = (nz1c[j] && nz2c[j]);

    // actual assignment of the nonzero
    if (!xor(rowsplit,colsplit)){
      if (nzr[i]<nzc[j]){
        ir[index_r] = i;
        jr[index_r] = j;
        index_r++;
      } else {
        ic[index_c] = i;
        jc[index_c] = j;
        index_c++;
      }
    } else {
      if (rowsplit) {
        ic[index_c] = i;
        jc[index_c] = j;
        index_c++;
      } else {
        ir[index_r] = i;
        jr[index_r] = j;
        index_r++;
      }
    }
    /*
    * putting the last element that could be chosen instead of the
    * k-th one, and we reduce the interval for randi by 1
    */
    matrix.i[k] = matrix.i[len-1];
    matrix.j[k] = matrix.j[len-1];
    len--;
  }

  // creation of vectors of the right size
  long* ir_n = vecallocl(index_r);
  long* jr_n = vecallocl(index_r);
  long* ic_n = vecallocl(index_c);
  long* jc_n = vecallocl(index_c);

  // copying only the filled part
  memcpy(ir_n,ir,index_r*SZLONG);
  memcpy(jr_n,jr,index_r*SZLONG);
  memcpy(ic_n,ic,index_c*SZLONG);
  memcpy(jc_n,jc,index_c*SZLONG);

  // creating the (dummy) values for the nonzeros
  double* val_r = vecallocd(index_r);
  double* val_c = vecallocd(index_c);

  for(k=0;k<index_r;k++)
    val_r[k] = 1.0;
  for(k=0;k<index_c;k++)
    val_c[k] = 1.0;

  // explicit creation of the final matrices
  struct sparsematrix Ar;
  Ar.NrNzElts = index_r;
  Ar.i = ir_n;
  Ar.j = jr_n;
  Ar.ReValue = val_r;

  struct sparsematrix Ac;
  Ac.NrNzElts = index_c;
  Ac.i = ic_n;
  Ac.j = jc_n;
  Ac.ReValue = val_c;
  
  // freeing memory from unnecessary arrays

  vecfreel(ir);
  vecfreel(jr);
  vecfreel(ic);
  vecfreel(jc);

  vecfreel(nz1c);
  vecfreel(nz2c);
  vecfreel(nzc);

  vecfreel(nz1r);
  vecfreel(nz2r);
  vecfreel(nzr);

  // explicit construction of the output
  struct TwoParts output;
  output.Ar = Ar;
  output.Ac = Ac;

  return output;
}

int main(){
  srand(time(NULL));
  FILE* File;
  struct sparsematrix matrix;
  if (!(File = fopen("matrices/test_matrix.mtx", "r"))) printf("Unable to open input matrix! Make sure it's the first parameter to the program\n");
  if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
  fclose(File);

  struct TwoParts two = localview(matrix);

  printf("===Ar===\n");
  print_matrix(reorder_col_incr(two.Ar));
  printf("\n\n");
  printf("===Ac===\n");
  print_matrix(reorder_col_incr(two.Ac));
  
}
