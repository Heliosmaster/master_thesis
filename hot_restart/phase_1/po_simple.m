function v=po_simple(A,ord)
[m,n]=size(A);
if ~ord
    v = 1:m+n;
else
    v = [m+1:m+n 1:m];
end
