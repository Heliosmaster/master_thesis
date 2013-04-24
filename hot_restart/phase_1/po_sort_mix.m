function [v] = po_sort_mix(A,strategy,varargin)
if nargin < 3
    widow = 1;
    ord = 'ascend';
    ord2 = 0;
elseif nargin < 4
    widow = varargin{1};
    ord = 'ascend';
    ord2 = 0;
elseif nargin < 5
    ord = varargin{2};
    ord2 = 0;
else
    ord = varargin{2};
    ord2 = varargin{3};
end
[m,~]=size(A);
nz=get_nnz(A);
[val,v] = sort_mix(nz,m,strategy,ord,ord2); 
if widow
    r = nnz(val==1);
    v = [v(r+1:end) v(1:r)];
end

