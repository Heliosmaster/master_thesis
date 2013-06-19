#include <stdio.h>
#include <stdlib.h>
#include <Mondriaan.h>
#include <string.h>

int main(int argc, char* argv[]){
	FILE* File;
	char inputname[100];
	if (argc <= 1){
		printf("Not enough parameters!\n");
		return 1;
	}
	sprintf(inputname,"%s",argv[1]);
	File = fopen(inputname, "r");

	struct sparsematrix matrix;
	if (!MMReadSparseMatrix(File, &matrix)) printf("Unable to read input matrix!\n");
	fclose(File);
	int k=0;

	char outputname[100];
	sprintf(outputname,"%s.edges",inputname);
	File = fopen(outputname, "w");
	for(k=0;k<matrix.NrNzElts;k++) fprintf(File,"%ld %ld\n",matrix.i[k],matrix.m+matrix.j[k]);
	fclose(File);
}
