% dim=0 row
% dim=1 col
function v=po_unsorted_mix(A,strategy,varargin)
[m,n]=size(A);
if nargin < 2
    ord = 0;
else
    ord = varargin{1};
end
rows = 1:m;
cols = (m+1):m+n;
if ~strategy
    v = mix_alternate(rows,cols,ord);
else
    v = mix_spread(rows,cols,ord);
end
