function [p,q,r,c]=sbdopt(I)

[m,n] = size(I);

nz1r = zeros(m,1);
nz1c = zeros(n,1);
nz2r = zeros(m,1);
nz2c = zeros(n,1);

[i,j,v] = find(I);

for k=1:nnz(I)
    if v(k) == 1
        nz1r(i(k)) = 1;
        nz1c(j(k)) = 1;
    end
    if v(k) == 2
        nz2r(i(k)) = 1;
        nz2c(j(k)) = 1;
    end
end

p0 = zeros(m,1);
q0 = zeros(n,1);

    countp1 = 0;
    countp2 = 0;
    countp3 = 0;
    countq1 = 0;
    countq2 = 0;
    countq3 = 0;

for k=1:m
    if nz1r(k) && ~nz2r(k)
        p0(k) = 1;
        countp1 = countp1 +1;
    elseif nz1r(k) && nz2r(k)
        p0(k) = 2;
        countp2 = countp2 +1;
    elseif ~nz1r(k) && nz2r(k)
        p0(k) = 3;
        countp3 = countp3+1;
    end
end
for k=1:n
    if nz1c(k) && ~nz2c(k)
        q0(k) = 1;
        countq1 = countq1+1;
    elseif nz1c(k) && nz2c(k)
        q0(k) = 2;
        countq2 = countq2 +1;
    elseif ~nz1c(k) && nz2c(k)
        q0(k) = 3;
        countq3 = countq3+1;
    end
end

% actual sorting of permutation vectors: 1 < 2 < 3 (red, cut, green)
% zp and zq are stored to compute the size of the parts
[~,p] = sort(p0);
[~,q] = sort(q0);

% row borders of blocks
r(1) = 1;
r(2) = countp1+r(1);
r(3) = countp2+r(2);
r(4) = countp3+r(3);

% column borders of blocks
c(1) = 1;
c(2) = countq1+c(1);
c(3) = countq2+c(2);
c(4) = countq3+c(3);
end