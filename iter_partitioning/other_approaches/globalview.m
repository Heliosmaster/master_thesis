% input: (m+n x m+n) matrix B constructed with the medium grain model
% globalview(B) tries to empty rows, by moving elements between Ar,Ac
function B=globalview(B,m,n)
    Niter = ceil((m+n)/10);
    Max_loss =ceil(nnz(B)/100);
    
    for j=1:Niter;
        [row,col,val] = find(B);
    
        % marks the row (and column) with a nonzero in the
        % diagonal of B, which indicates that that col (if <=n) or row is
        % split. 
        dia = zeros(m+n,1);
        for i=1:length(row)
            if row(i) == col(i)
                dia(row(i))=1;
            end
        end

        % find the indices of the marked row
        ind_dia = find(logical(dia));

        %computation of the nonzeros of the rows of B
        nzi = zeros(m+n,1);
        B2 = B';
        for i=1:m+n
            nzi(i) = nnz(B2(:,i));
        end

        % finds the minimum number of nonzeros in row that have a diagonal
        % element (local index)
        [v,i] = min(nzi(logical(dia)));

        % translate the index back to an index of the original matrix (global
        % index), i is now the row to be emptied
        i = ind_dia(i);

        % positions of elements of row i in our list of nonzeros
        indices = find(row==i);
        loss = 0;
        for k=1:v
            r1 = row(indices(k));
            c1 = col(indices(k));
            if r1 == c1 %diagonal element, we don't care about that nonzero
                continue; 
            else
                if nnz(B(c1,:))
                    % swap row and column of the nonzero
                    row(indices(k)) = c1;
                    col(indices(k)) = r1;
                else
                    if loss <= Max_loss
                        row(indices(k)) = c1;
                        col(indices(k)) = r1;
                        loss = loss+1;
                       % fprintf('Row %g added!\n',i);
                    end
                end
            end

        end

        B = sparse(row,col,val,m+n,m+n);
        B2 = B';

        for i=1:m+n
            if (nnz(B2(:,i)) == 1 || nnz(B(:,i))==1 ) && (B(i,i) == 1)
                B(i,i) = 0;
               % fprintf('Row %g emptied!\n',i);
            end
        end
        
        for i=1:m+n
            if nnz(B2(:,i)) && nnz(B(:,i))
                B(i,i) = 1;
            end
        end
    end        
end