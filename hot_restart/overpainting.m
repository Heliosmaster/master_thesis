% A matrix
% v vector of priorities
function [Ac,Ar] = overpainting(A,v)
[m,n] = size(A);
[i,j,s] = find(A);
%[i1,index1] = sort(i);
%j1 = j(index1); 
%s1 = s(index1); 
for z=m+n:-1:1;
    k = v(z);
    if k<=m
        %it's a row
      
        s(i==k) = 10;
    else
        %it's a column
        s(j==(k-m)) = 11;
        
    end
end
ir = i(s==10);
jr = j(s==10);

ic = i(s==11);
jc = j(s==11);

Ar = sparse(ir,jr,ones(size(ir)),m,n);
Ac = sparse(ic,jc,ones(size(ic)),m,n);


