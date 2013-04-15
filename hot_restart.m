%function [Ac,Ar]=hot_restart(A)
[m,n] = size(A);
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

[It,Jt,~] = find(At);

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

nz_tot = [nzr; nzc];

[nz_sorted, sort_index] = sort(nz_tot);
%[nzr_sorted, sort_index_r] = sort(nzr);
%    [nzc_sorted, sort_index_c] = sort(nzc);

blocked = zeros(m+n,1);
index = 1;

index_r = 1;
index_c = 1;

while(index <= m+n)
    
    id = sort_index(index);
    fprintf('id: %g ',id);
    if ~blocked(id) == 1;
        % forget about the ones with the 1
        if nz_sorted(index) == 1
            blocked(id) = 1;
            fprintf('1!\n');
            % maybe force here that it should go to the other dimension
        else
            % is it a row or a column ?
            if (id<=m)
                fprintf('row!\n'); %it's a row
                index_at = 1;
                
                while(Jt(index_at) <= id && index_at < m+n)
                    if Jt(index_at) == id
                        j = It(index_at);
                        i = Jt(index_at);
                        ir(index_r) = i;
                        jr(index_r) = j;
                        index_r = index_r+1;
                        blocked(m+j) = 1;
                    end
                    index_at = index_at+1;
                end
            else
            fprintf('column!\n');  %it's a column, put all its elements in Ac
                index_a = 1;
                while(J(index_a) <= id-m && index_a < m+n)
                    if J(index_a) == id-m
                        i = I(index_a);
                        j = J(index_a);
                        ic(index_c) = i;
                        jc(index_c) = j;
                        index_c = index_c+1;
                        blocked(i) = 1;
                    end
                    index_a = index_a+1;
                end
                
            end
        end
    else
        fprintf('blocked!\n');
    end
    index = index+1;
    
end





%end