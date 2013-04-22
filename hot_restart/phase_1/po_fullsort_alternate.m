function [v] = po_fullsort_alternate(A,varargin)
if nargin < 2
    ord = 'ascend';
    ord2 = 'row';
elseif nargin < 3
    ord = varargin{1};
    ord2 = 'row';
else
    ord = varargin{1};
    ord2 = varargin{2};
end
[m,~]=size(A);
nz=get_nnz(A);
[~,iu] = sort_alternate(nz,m,ord,ord2);
v = nz(iu);