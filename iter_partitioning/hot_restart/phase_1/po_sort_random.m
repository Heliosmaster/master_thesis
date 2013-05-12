function [v] = po_sort_random(A,varargin)
if nargin < 2
    widow = 1;
    ord = 'ascend';
elseif nargin < 3
    widow = varargin{1};
    ord = 'ascend'
else
    widow = varargin{1};
    ord = varargin{2};
end
[m,~]=size(A);
nz=get_nnz(A);
[val,v] = sort_random(nz,m,ord);
if widow
    r = nnz(val==1);
    v = [v(r+1:end) v(1:r)];
end