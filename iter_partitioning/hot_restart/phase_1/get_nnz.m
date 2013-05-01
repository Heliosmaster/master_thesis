% nz=get_nnz(A)
%
% returns the array of length m+n (m rows, n columns, in this order) nz
% such that nz(i) = # of nonzeros of row/column i
function nz=get_nnz(A)
[m,n]=size(A);

%transposing the matrix for fast access to the rows
At = A';

%initialization of the output vector
nz = zeros(1,m+n);

%computing nonzeros for the rows
for i=1:m
    nz(i) = nnz(At(:,i));
end
%computing nonzeros for the columns
for i=m+1:m+n
    nz(i) = nnz(A(:,i-m));
end

