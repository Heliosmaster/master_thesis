%A split matrix with 1 and 2
function v=get_split(A)
[m,n]=size(A);
nz1 = get_nnz(A==1);
nz2 = get_nnz(A==2);
v = zeros(1,m+n);
for i=1:m+n
    v(i) = (nz1(i)) && (nz2(i));
end


