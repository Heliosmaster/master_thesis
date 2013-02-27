% A = sparse matrix with values 1 and 2
% TODO: construction of sparse matrices by indices and 'sparse' to speed up
%       Breaking ties randomly (for the 1st case)?

function [Ac,Ar]=localview(A)
    [m,n] = size(A);
    [I,J,V] = find(A);
    Ar = sparse(m,n);
    Ac = sparse(m,n);
    [i1,j1,s1] = find(A==1);
    [i2,j2,s2] = find(A==2);
    A1 = sparse(i1,j1,s1,m,n);
    A2 = sparse(i2,j2,s2,m,n);
    
    %spy(A1,'r'); hold on;
    %spy(A2,'g'); hold off;
    %ir = [];
    %ic = [];
    %jr = [];
    %jc = [];
    len = length(I);
    while(len>0) 
        k = ceil(len*rand(1)); %apparently much faster than k = randi([1,len]); 0.01s vs 0.3s
        i = I(k);
        j = J(k);
        %fprintf('picked (%g,%g) - ',i,j);
        rowsplit = (nnz(A1(i,:))) && (nnz(A2(i,:)));
        colsplit = (nnz(A1(:,j))) && (nnz(A2(:,j)));
        if (~xor(rowsplit,colsplit))
            if nnz(A(i,:)) < nnz(A(:,j))
                %ir = [ir i];
                %jr = [jr j];
                Ar(i,j) = 1;
                %fprintf('row!\n');
            else
                %ic = [ic i];
                %jc = [jc j];
                Ac(i,j) = 1;
                %fprintf('col!\n');
            end
        else
            if rowsplit
                Ac(i,j) = 1;
                %ic = [ic i];
                %jc = [jc j];
                %fprintf('col!\n');
            else
                Ar(i,j) = 1;
                %ir = [ir i];
                %jr = [jr j];
                %fprintf('row!\n');
            end
        end
        I(k) = [];
        J(k) = [];
        len = len-1;
    end
%     vr = ones(length(jr),1);
%     vc = ones(length(jc),1);
%     Ar = sparse(ir,jr,vr,m,n);
%     Ac = sparse(ic,jc,vc,m,n);
end
    
    
