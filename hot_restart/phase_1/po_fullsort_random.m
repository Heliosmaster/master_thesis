function [v] = po_fullsort_random(A,varargin)
if nargin < 2
    ord = 'ascend';
else
    ord = varargin{1};
end
[m,~]=size(A);
nz=get_nnz(A);
[~,iu] = sort_random(nz,m,ord);
v = nz(iu);