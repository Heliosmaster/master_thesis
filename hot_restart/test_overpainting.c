#include "overpainting.c"

int main(){
  
  /* reading the matrix from file */
  FILE* File;
  struct sparsematrix matrix;
  File = fopen("../matrices/test_matrix.mtx", "r");
  if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
  fclose(File);

  /* creating explicitly a particular priority vector vec */
  int m = matrix.m;
  int n = matrix.n;

  long* vec = vecallocl(m+n);
  int i;  

  vec[0]= 2;
  vec[1]= 3;
  vec[2]= 10;
  vec[3]= 11;
  vec[4]= 15;
  vec[5]= 5;
  vec[6]= 1;
  vec[7]=6;
  vec[8]=14;
  vec[9]=13;
  vec[10]=8;
  vec[11]=7;
  vec[12]=9;
  vec[13]=0;
  vec[14]=12;
  vec[15]=16;
  vec[16]=17;
  vec[17]=4;

  /* explicit computation of Ar and Ac with the overpaint method */
  struct twomatrices two = overpaint(&matrix,vec);

  /* printing out the values */
  printf("===A===\n");
  print_matrix(two.Ar);
  printf("===B===\n");
  print_matrix(two.Ac);
}