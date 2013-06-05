#include "overpaint.h"

int main(){
  
  /* reading the matrix from file */
  FILE* File;
  struct sparsematrix matrix;
  File = fopen("../../matrices/cre_b.mtx", "r");
  /* File = fopen("../../matrices/tbdlinux.mtx", "r"); */
  if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
  fclose(File);

  /* creating explicitly a particular priority vector vec */
  int m = matrix.m;
  int n = matrix.n;

  if(matrix.ReValue == NULL){
    matrix.ReValue = vecallocd(matrix.NrNzElts);
    int j;
    for(j=0;j<matrix.NrNzElts;j++) matrix.ReValue[j] = 0.0;
  }

  /*long* vec = random_permutation(m+n); */
  int i;
  long* vec = vecallocl(m+n);
  for(i=0;i<m+n;i++) vec[i]=i;

  /* explicit computation of Ar and Ac with the overpaint method */
  struct sparsematrixplus m2plus = reorder_row_incr(&matrix);
  struct sparsematrix matrix2 = m2plus.matrix;
  struct twomatrices two = overpaint(&matrix2,vec);

  printf("---------------\n");
/*print_matrix(two.Ar);
  print_matrix(two.Ac); */

  vecfreel(vec);
  vecfreel(m2plus.perm);

  MMDeleteSparseMatrix(&matrix);
  MMDeleteSparseMatrix(&matrix2);
  MMDeleteSparseMatrix(&two.Ar);
  MMDeleteSparseMatrix(&two.Ac);
}
