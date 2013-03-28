#define SZINT (sizeof(int))
#define SZDBL (sizeof(double))
#define SZLONG (sizeof(long))

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
    long *pi;

    if (n==0){
        pi= NULL; 
    } else { 
        pi= (long *)malloc(n*SZLONG);
        if (pi==NULL)
            printf("vecalloci: not enough memory\n");
    }
    return pi;

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

void vecfreel(long *pd){
    /* This function frees a vector of longs */

    if (pd!=NULL)
        free(pd);

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

struct sparsematrix reorder_col_incr(struct sparsematrix* matrix){
    long length = matrix->NrNzElts;
    long* I = vecallocl(length);
    long* J = vecallocl(length);
    double* Val = vecallocd(length);

    int k,l;

    long* tempArray = vecallocl(length);
    for(k=0;k<length;k++) tempArray[k] = matrix->j[k];

    struct sparsematrix newmatrix;

    long* indices = QSort(tempArray,length);

    for(l=0;l<length;l++){
        k = indices[length-l-1];
        I[l] = matrix->i[k];
        J[l] = matrix->j[k];
        Val[l] = matrix->ReValue[k];

    }

    newmatrix.i = I;
    newmatrix.j = J;
    newmatrix.ReValue = Val;
    newmatrix.NrNzElts = length;
    vecfreel(indices);
    vecfreel(tempArray);
    return newmatrix;
}