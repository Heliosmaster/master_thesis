function v=po_simple(A,varargin)
if nargin < 2
    ord = 'row';
else
    ord = varargin{1};
end
[m,n]=size(A);
if strcmp(ord,'row');
    v = 1:m+n;
else
    v = [m+1:m+n 1:m];
end
