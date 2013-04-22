function [v,l] = pa_fullsort_random(A,varargin)
if nargin < 2
    ord = 'ascend';
else
    ord = varargin{1};
end
[m,~]=size(A);
[uncut,cut]=uncut_before_cut(A);
l = length(uncut);
nz=get_nnz(A);
[~,iu] = sort_random(nz(uncut),m,ord);
[~,ic] = sort_random(nz(cut),m,ord);
v = [uncut(iu) cut(ic)];