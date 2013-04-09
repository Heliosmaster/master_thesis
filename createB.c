#include "Localview.c"

struct sparsematrix createB(struct sparsematrix* Ac, struct sparsematrix* Ar){

  int k = 0; /* counter for the elements added to B */

  /* explicit saving of m,n for brevity */
  int m = Ar->m;
  int n = Ac->n;

  /* 
  * building the bookkeeping vectors
  * nzXr = nonzeros in the rows of AX
  * nzXc = nonzeros in the columns of AX
  */

  long* nzrr = nnz(Ar->i, Ar->NrNzElts, m);
  long* nzcr = nnz(Ac->i, Ac->NrNzElts, m);

  long* nzrc = nnz(Ar->j, Ar->NrNzElts, n);
  long* nzcc = nnz(Ac->j, Ac->NrNzElts, n);

  /* 
  * initial allocation of space for B, at most
  * all the nonzeros of A and the diagonal filled)
  */
  long maxLength = (Ar->NrNzElts)+(Ac->NrNzElts)+m+n;

  /* vectors for the coordinates of B */
  long* bi = vecallocl(maxLength);
  long* bj = vecallocl(maxLength);

  int i;

  /* diagonal part */

  for(i=0;i<n;i++){
    if (nzrc[i] && nzcc[i]){
      bi[k] = i;
      bj[k] = i;
      k++;
    }
  }

  for(i=0;i<m;i++){
    if (nzrr[i] && nzcr[i]){
      bi[k] = n+i;
      bj[k] = n+i;
      k++;
    }
  }

  /* bottom left corner (row shifted by n) */
  for(i=0;i<Ac->NrNzElts;i++){
    bi[k] = Ac->i[i]+n;
    bj[k] = Ac->j[i];
    k++;
  }

  /* top right corner */
  for(i=0;i<Ar->NrNzElts;i++){
    bi[k] = Ar->j[i];
    bj[k] = Ar->i[i]+n;
    k++;
  }


  /* compression of the vectors */
  long* bi_n = vecallocl(k);
  long* bj_n = vecallocl(k);

  memcpy(bi_n,bi,k*SZLONG);
  memcpy(bj_n,bj,k*SZLONG);

  vecfreel(bi);
  vecfreel(bj);

  /* creation of the (dummy) values */
  double* bval = vecallocd(k);
  double* bim = vecallocd(k);

  for(i=0;i<k;i++){
    bval[i] = 1.0;
   /* bim[i] = 0.0; */
  } 

  struct sparsematrix B;
  B.i = bi_n;
  B.m = m+n;
  B.n = m+n;
  B.j = bj_n;
  B.ReValue = bval;
  B.ImValue = bim;
  B.NrNzElts = (long)k;

  return B;
}

int main(){
  /* srand(time(NULL)); */
  /* reading the matrix from file */
  FILE* File;
  struct sparsematrix matrix;
  File = fopen("matrices/test_matrix.mtx", "r");
  if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
  fclose(File);

  struct twomatrices A = split1and2(&matrix);
  struct sparsematrix B = createB(&(A.Ac),&(A.Ar));
  print_matrix(reorder_col_incr(&B));
}