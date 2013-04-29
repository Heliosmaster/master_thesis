#include "overpainting.c"

int main(){
  /* srand(time(NULL)); */
  /* reading the matrix from file */
  FILE* File;
  struct sparsematrix matrix;
  File = fopen("../matrices/test_matrix.mtx", "r");
  if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
  fclose(File);

  struct sparsematrixplus matrix2 = reorder_col_incr(&matrix);
  //struct sparsematrixplus matrix3 = reorder_row_incr(&(matrix2.matrix));

  int m = matrix.m;
  int n = matrix.n;

  long* vec = vecallocl(m+n);
  int i;  
  /*for(i=0;i<m+n;i++) vec[i] = m+n-i-1; */
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

  //print_vec_inline(vec,m+n);

  /*struct twomatrices two = overpaint_col(&matrix2,vec);*/
  struct twomatrices two = overpaint(&matrix,vec);

  
  printf("===A===\n");
  print_matrix(two.Ar);
  printf("===B===\n");
  print_matrix(two.Ac);


/*  printf("===A===\n");
  print_matrix(matrix);
  printf("===B===\n");
  print_matrix(matrix2.matrix);
  printf("===C===\n");
  print_matrix(matrix3.matrix);*/

  
  // //update_rows_link(&matrix, &matrix2.matrix,0,10,reverse_perm(matrix2.perm,matrix.NrNzElts));
  // //update_cols_link(&matrix2.matrix, &matrix,0,10,matrix2.perm);
  // print_matrix(matrix2.matrix);
  // printf("\n");
  // print_vec_inline(matrix2.perm,matrix.NrNzElts);
  // print_vec_inline(reverse_perm(matrix2.perm,matrix.NrNzElts),matrix.NrNzElts);
}