function [p,q,r,c,A1,A2]=sbd(I)

    [m,n] = size(I);
    
    % separating the green and red part
    [i1,j1,v1] = find(I==1);
    [i2,j2,v2] = find(I==2);
    
    % initialization of the permutation vectors
    p0 = zeros(m,1);
    q0 = zeros(n,1);

    % marking of the cut rows/columns
    % 1: red row/column
    % 2: cut row/column
    % 3: green row/column
    for i=1:m
        if find(i1==i);
            if find(i2==i)
                p0(i) = 2;
            else
                p0(i) = 1; 
            end
        else
            p0(i) = 3; 
        end
    end

    for i=1:n
        if find(j1==i);
            if find(j2==i)
                q0(i) = 2;
            else
                q0(i) = 1;
            end
        else
            q0(i) = 3;
        end
    end

    A1 = sparse(i1,j1,v1,m,n);
    A2 = sparse(i2,j2,v2,m,n);


    [zp,p] = sort(p0);
    [zq,q] = sort(q0);

    r(1) = 1;
    r(2) = length(find(zp==1))+r(1);
    r(3) = length(find(zp==2))+r(2);
    r(4) = length(find(zp==3))+r(3);


    c(1) = 1;
    c(2) = length(find(zq==1))+c(1);
    c(3) = length(find(zq==2))+c(2);
    c(4) = length(find(zq==3))+c(3);
end

% figure;
% spy(A1(p,q),'r'); hold on; spy(A2(p,q),'g');