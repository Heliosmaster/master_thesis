function [v] = po_sorted_mix(A,strategy,varargin)
if nargin < 3
    widow = 1;
    colFirst = 0;
elseif nargin < 4
    widow = varargin{1};
    colFirst = 0;
else
    widow = varargin{1};
    colFirst = varargin{2};
end
[m,~]=size(A);
nz=get_nnz(A);
[val,v] = sort_mix(nz,m,strategy,colFirst); 
if widow
    r = nnz(val==1);
    v = [v(r+1:end) v(1:r)];
end
