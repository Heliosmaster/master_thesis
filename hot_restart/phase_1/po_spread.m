% dim=0 row
% dim=1 col
function v=po_spread(A,varargin)
[m,n]=size(A);
if nargin < 2
    ord = 0;
else
    ord = varargin{1};
end
v = mix_spread(1:m,m+1:n,ord);