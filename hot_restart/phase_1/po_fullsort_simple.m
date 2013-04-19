function v=po_fullsort_simple(A)
nz=get_nnz(A);
[~,v] = sort(nz);