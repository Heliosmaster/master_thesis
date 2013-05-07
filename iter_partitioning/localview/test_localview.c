#include "Localview.c"

int main(){
  /* srand(time(NULL)); */
  /* reading the matrix from file */
  FILE* File;
  struct sparsematrix matrix;
//File = fopen("../../matrices/test_matrix.mtx", "r");
  File = fopen("../../matrices/m_testbed/tbdlinux.mtx", "r");

  if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
  fclose(File);

  /* actual split */
  struct twomatrices two = localview(&matrix);

  /* print out for checking 
  printf("===Ar===\n");
  print_matrix(two.Ar);
  printf("\n");
  printf("===Ac===\n");
  print_matrix(two.Ac); */
}
