function v=po_colrow(A)
[m,n]=size(A);
v = [m+1:m+n 1:m];