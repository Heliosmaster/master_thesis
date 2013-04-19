function [v,l]=pa_fullsort_simple(A)
[uncut,cut]=uncut_before_cut(A);
l = length(uncut);
nz=get_nnz(A);
[~,iu] = sort(nz(uncut));
[~,ic] = sort(nz(cut));
v = [uncut(iu) cut(ic)];