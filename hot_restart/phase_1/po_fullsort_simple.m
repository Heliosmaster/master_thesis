function v=po_fullsort_simple(A,varargin)
if nargin < 2
    ord = 'ascend';
else
    ord = varargin{1};
end
nz=get_nnz(A);
[~,v] = sort(nz,ord);