% A = sparse matrix with values 1 and 2
% TODO: Breaking ties randomly (for the 1st case)?

function [Ac,Ar]=localview(A)
    [m,n] = size(A);
    
    % using 3 vectors for representing nnz of A
    [I,J,~] = find(A);
    
    %initialization of Ar Ac
    Ar = sparse(m,n);
    Ac = sparse(m,n);
    
    % distinguish the two partitioned part from input
    [i1,j1,s1] = find(A==1);
    [i2,j2,s2] = find(A==2);
    A1 = sparse(i1,j1,s1,m,n);
    A2 = sparse(i2,j2,s2,m,n);
    
    len = length(I);
    
    % until there's something yet to assign to either Ar or Ac
    while(len>0) 
        
        % choose a random number between 1 and len. we have the nonzero
        % (i,j)
        k = ceil(len*rand(1)); %apparently much faster than k = randi([1,len]); 0.01s vs 0.3s
        i = I(k);
        j = J(k);
        
        %check whether both A1 and A2 have nonzeros at row i, i.e. row is
        %split
        rowsplit = (nnz(A1(i,:))) && (nnz(A2(i,:)));
        
        %check whether both A1 and A2 have nonzeros at col j, i.e. col j is
        %split
        colsplit = (nnz(A1(:,j))) && (nnz(A2(:,j)));
        
        % check whether they are bot split or both unsplit
        if (~xor(rowsplit,colsplit))
            
            %check whether the row is shorter than the col
            if nnz(A(i,:)) < nnz(A(:,j))
                Ar(i,j) = 1;
            else
                Ac(i,j) = 1;
            end
        else
            %if only the row is split, assign to column
            if rowsplit
                Ac(i,j) = 1;
            else
            %if only col is split, assign to row
                Ar(i,j) = 1;
            end
        end
        
        %remove (i,j) from the lists, so that it does not get picked again
        I(k) = [];
        J(k) = [];
        len = len-1;
    end
end
    
    
