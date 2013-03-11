function [p,q,r,c]=super_sbd(I)
    
    %initial canonical SBD form
    [p,q,r,c] = sbd(I);
    [P1,P2,P3,P4,P5,P6,P7] = split_subparts(I,p,q,r,c);

    %getting the dimension of the subparts
    m1 = size(P2,1);
    n1 = size(P1,2);
    m2 = size(P3,1);
    n2 = size(P2,2);
    m3 = size(P7,1);
    n3 = size(P7,2);

    % vectors that track whether a line/column is empty or not
    nz2 = zeros(m1,1);
    nz3 = zeros(n1,1);
    nz5 = zeros(n3,1);
    nz6 = zeros(m3,1);

  
    for i=1:m1
    nz2(i) = logical(nnz(P2(i,:)));
    end

    for i=1:n1
    nz3(i) = logical(nnz(P3(:,i)));
    end


    for i=1:m3
    nz6(i) = logical(nnz(P6(i,:)));
    end

    for i=1:n3
     nz5(i) = logical(nnz(P5(:,i)));
    end

    % sorting block 2 and 3 for the upper left corner (block 1)
    [zp2,p2] = sort(nz2);
    [zp3,p3] = sort(nz3);

    % sorting in reverse block 5 and 6 for the lower right corner (block 7) 
    [zp5,p5] = sort(nz5,'descend');
    [zp6,p6] = sort(nz6,'descend');

    % permutation vectors: the central part is the identity permutation
    % because they don't get sorted in that dimension
    p = [p2; (m1+1:m1+m2)'; m1+m2+p6];
    q = [p3; (n1+1:n1+n2)'; n1+n2+p5];

    % bookkeeping of the sizes of the new subparts
    r(1) = 1;
    r(2) = length(find(zp2==0))+r(1);
    r(3) = length(find(zp2==1))+r(2);
    r(4) = m2+r(3);
    r(5) = length(find(zp6==1))+r(4);
    r(6) = length(find(zp6==0))+r(5);

    c(1) = 1;
    c(2) = length(find(zp3==0))+c(1);
    c(3) = length(find(zp3==1))+c(2);
    c(4) = n2+c(3);
    c(5) = length(find(zp5==1))+c(4);
    c(6) = length(find(zp5==0))+c(5);
end


