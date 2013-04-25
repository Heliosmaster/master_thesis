function v=po_simple(A,varargin)
if nargin < 2
    ord = 'ascend';
else
    ord = varargin{1};
end
[m,n]=size(A);
if strcomp(ord,'ascend');
    v = 1:m+n;
else
    v = [m+1:m+n 1:m];
end
