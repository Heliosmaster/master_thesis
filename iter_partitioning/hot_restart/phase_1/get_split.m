% v = get_split(A)
% 
% returns a m+n logical vector (rows and then columns)
% nz(i) = 1 if the row/column is split (has at least a 1 and a 2)
% nz(i) = 0 otherwise
%
% A needs to be a split matrix with 1 and 2 as nonzero values

function v=get_split(A)
[m,n]=size(A);

% separating the two parts
nz1 = get_nnz(A==1);
nz2 = get_nnz(A==2);

%initialization of the output
v = zeros(1,m+n);

% computation of the final values
for i=1:m+n
    v(i) = (nz1(i)) && (nz2(i));
end


