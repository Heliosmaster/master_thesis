function [v] = po_fullsort_spread(A,varargin)
if nargin < 2
    ord = 'ascend';
    ord2 = 0;
elseif nargin < 3
    ord = varargin{1};
    ord2 = 0;
else
    ord = varargin{1};
    ord2 = varargin{2};
end
[m,~]=size(A);
nz=get_nnz(A);
[~,iu] = sort_spread(nz,m,ord,ord2);
v = nz(iu);