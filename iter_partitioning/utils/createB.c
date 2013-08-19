#include "createB.h"

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

  /* freeing the vector used for the diagonal part */
  vecfreel(nzrc);
  vecfreel(nzcc);
  vecfreel(nzrr);
  vecfreel(nzcr);

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

	struct sparsematrix B;
	MMSparseMatrixInit(&B);
	B.m = m+n;
	B.n = m+n;
	B.NrNzElts = (long)k;
	MMSparseMatrixAllocateMemory(&B);
	
  memcpy(B.i,bi,B.NrNzElts*SZLONG);
  memcpy(B.j,bj,B.NrNzElts*SZLONG);

  vecfreel(bi);
  vecfreel(bj);

  /* creation of the (dummy) values */

  for(i=0;i<k;i++) B.ReValue[i] = 1.0;

  return B;
}

/* function that from a partitioned B retrieves A with new partitioning */
struct sparsematrix decomposeB(struct sparsematrix* B, int m, int n){
	int index_B;
	int index_A = 0;
	int count=0;
	for(index_B=0;index_B<B->NrNzElts;index_B++) if(B->i[index_B] != B->j[index_B]) count++;

	struct sparsematrix A;
	MMSparseMatrixInit(&A);
	A.NrNzElts = (long)count;
	A.m = m;
	A.n = n;
	MMSparseMatrixAllocateMemory(&A);
	for(index_B = 0; index_B < B->NrNzElts; index_B++){
		if(B->i[index_B] == B->j[index_B]) continue;
		/* check whether the given nonzero is in the part of Ar^T or Ac */
		if(B->i[index_B] < n) {
			/* belong to Ar^T */
			A.i[index_A] = B->j[index_B]-n;
			A.j[index_A] = B->i[index_B];
		}	
		else {
			A.i[index_A] = B->i[index_B]-n;
			A.j[index_A] = B->j[index_B];
			/* belongs to Ac */
		}
		A.ReValue[index_A] = B->ReValue[index_B];
		index_A++;
	}
	return A;
}
