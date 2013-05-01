function v=po_rand_order(A)
[m,n]=size(A);
v=randperm(m+n);