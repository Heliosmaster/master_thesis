#include "localview.h"
#include "po_localview.h"

int main(){
  /* srand(time(NULL)); */
  /* reading the matrix from file */
  FILE* File;
  struct sparsematrix matrix;
  File = fopen("../../matrices/test_matrix.mtx", "r");

  if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
  fclose(File);

  /* actual split */
  struct twomatrices two = localview(&matrix);
	struct twomatrices three = po_localview(&matrix);

 /* print out for checking  */
  printf("===Ar===\n");
  print_matrix(two.Ar);
  printf("\n");
  printf("===Ac===\n");
  print_matrix(two.Ac);
	printf("----------------------\n");
  printf("===Ar===\n");
  print_matrix(three.Ar);
  printf("\n");
  printf("===Ac===\n");
  print_matrix(three.Ac); 


  MMDeleteSparseMatrix(&matrix);
  MMDeleteSparseMatrix(&two.Ar);
  MMDeleteSparseMatrix(&two.Ac);
  MMDeleteSparseMatrix(&three.Ar);
  MMDeleteSparseMatrix(&three.Ac);
	exit(0);
}
