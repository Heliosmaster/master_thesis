function v=po_sort_simple(A,varargin)
if nargin < 2
    widow = 1;
    ord = 'ascend';
elseif nargin < 3
    widow = varargin{1};
else
    widow = varargin{1};
    ord = varargin{2};
end
nz=get_nnz(A);
[val,v] = sort(nz,ord);
if widow
    r = nnz(val==1);
    v = [v(r+1:end) v(1:r)];
end