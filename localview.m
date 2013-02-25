% A = sparse matrix with values either 1 or 2
% TODO: construction of sparse matrices by indexes and 'sparse' to speed up
%       breaking ties randomly (for the 1st case)?

function [Bc,Br]=localview(A)
    [m,n] = size(A);
    Br = sparse(m,n);
    Bc = sparse(m,n);
    [m,n] = size(A);
    [i1,j1,s1] = find(A==1);
    A1 = sparse(i1,j1,s1,m,n);
    [i2,j2,s2] = find(A==2);
    A2 = sparse(i2,j2,s2,m,n);
    [I,J] = find(A);
    %spy(A1,'r'); hold on;
    %spy(A2,'g'); hold off;
    
    len = length(I);
    while(len>0) 
        k = randi([1,len]);
        i = I(k);
        j = J(k);
        %fprintf('picked (%g,%g) - ',i,j);
        rowsplit = (nnz(A1(i,:))) && (nnz(A2(i,:)));
        colsplit = (nnz(A1(:,j))) && (nnz(A2(:,j)));
        if (~xor(rowsplit,colsplit))
            if nnz(A(i,:)) < nnz(A(:,j))
                Br(i,j) = 1;
                %fprintf('row!\n');
            else
                Bc(i,j) = 1;
                %fprintf('col!\n');
            end
        else
            if rowsplit
                Bc(i,j) = 1;
                %fprintf('col!\n');
            else
                Br(i,j) = 1;
                %fprintf('row!\n');
            end
        end
        I(k) = [];
        J(k) = [];
        len = len-1;
    end
end
    
    
