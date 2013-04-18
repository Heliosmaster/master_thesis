function nz=get_nnz(A)
[m,n]=size(A);
At = A';
nz = zeros(1,m+n);
for i=1:m
    nz(i) = nnz(At(:,i));
end
for i=m+1:m+n
    nz(i) = nnz(A(:,i-m));
end
end

