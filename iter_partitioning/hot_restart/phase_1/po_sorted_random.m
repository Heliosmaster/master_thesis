function [v] = po_sorted_random(A,varargin)
if nargin < 2
    widow = 1;
else
    widow = varargin{1};
end
[m,~]=size(A);
nz=get_nnz(A);
[val,v] = sort_random(nz,m,'ascend');
if widow
    r = nnz(val==1);
    v = [v(r+1:end) v(1:r)];
end