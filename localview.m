% A = sparse matrix with values 1 and 2
% TODO: Breaking ties randomly (for the 1st case)?

function [Ac,Ar]=localview(A)
    [m,n] = size(A);
    
    % using 3 vectors for representing nnz of A
    [I,J,~] = find(A);
    
    %initialization of Ar Ac
%     Ar = sparse(m,n);
%     Ac = sparse(m,n);
%     
    % distinguish the two partitioned part from input
    [i1,j1,s1] = find(A==1);
    [i2,j2,s2] = find(A==2);
    A1 = sparse(i1,j1,s1,m,n);
    A2 = sparse(i2,j2,s2,m,n);
    
    A1t = A1';
    A2t = A2';
    At = A';
    
    len = length(I);
    
    nz1c = zeros(n,1);
    nz2c = zeros(n,1);
    nzc = zeros(n,1);
    nz1r = zeros(m,1);
    nz2r = zeros(m,1);
    nzr = zeros(m,1);
    for i=1:n
        nz1c(i) = nnz(A1(:,i));
        nz2c(i) = nnz(A2(:,i));
        nzc(i) = nnz(A(:,i));
    end
    
    for i=1:m
        nz1r(i) = nnz(A1t(:,i));
        nz2r(i) = nnz(A2t(:,i));
        nzr(i) = nnz(At(:,i));
    end
    
     ic = zeros(size(I));
     jc = zeros(size(I));
     ir = zeros(size(I));
     jr = zeros(size(I));
     
     index_r = 1;
     index_c = 1;
%     
    % until there's something yet to assign to either Ar or Ac
    while(len>0) 
        
        % choose a random number between 1 and len. we have the nonzero
        % (i,j)
        k = ceil(len*rand(1)); %apparently much faster than k = randi([1,len]); 0.01s vs 0.3s
        i = I(k);
        j = J(k);
        
        %check whether both A1 and A2 have nonzeros at row i, i.e. row is
        %split
        
        rowsplit = (nz1r(i)) && (nz2r(i));
        
        %check whether both A1 and A2 have nonzeros at col j, i.e. col j is
        %split
        colsplit = (nz1c(j)) && (nz2c(j));
        
        % check whether they are bot split or both unsplit
        if (~xor(rowsplit,colsplit))
            
            %check whether the row is shorter than the col
            if nzr(i) < nzc(j)
%                Ar(i,j) = 1;
               ir(index_r) = i;
               jr(index_r) = j;
               index_r = index_r+1;
            else
%                 Ac(i,j) = 1;
               ic(index_c) = i;
               jc(index_c) = j;
               index_c = index_c+1;
            end
        else
            %if only the row is split, assign to column
            if rowsplit
%                Ac(i,j) = 1;
               ic(index_c) = i;
               jc(index_c) = j;
               index_c = index_c+1;
            else
            %if only col is split, assign to row
%                 Ar(i,j) = 1;
               ir(index_r) = i;
               jr(index_r) = j;
               index_r = index_r+1;

            end
        end
        
        %remove (i,j) from the lists, so that it does not get picked again
        I(k) = I(len);
        J(k) = J(len);
        len = len-1;
    end
    ir = nonzeros(ir);
    jr = nonzeros(jr);
    ic = nonzeros(ic);
    jc = nonzeros(jc);
    
    Ar=sparse(ir,jr,ones(size(ir)),m,n);
    Ac=sparse(ic,jc,ones(size(ic)),m,n);
end
    
    
