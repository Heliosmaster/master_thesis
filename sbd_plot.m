% sbd_plot(I,p,q,r,c)
%
% given [p,q,r,c]=sbd(I) prints a figure with all the 7 blocks of the SBD
% form in a different color
% note: shares code with sbdview
function sbd_plot(I,p,q,r,c)
    [m,n] = size(I);
    [P1,P2,P3,P4,P5,P6,P7] = split_subparts(I,p,q,r,c);

    % computes the size of the blocks
    mi = [r(2)-r(1),r(3)-r(2),r(4)-r(3)];
    ni = [c(2)-c(1),c(3)-c(2),c(4)-c(3)];
    
    % converting to vectors
    [i1,j1,~] = find(P1);
    [i2,j2,~] = find(P2);
    [i3,j3,~] = find(P3);
    [i4,j4,~] = find(P4);
    [i5,j5,~] = find(P5);
    [i6,j6,~] = find(P6);
    [i7,j7,~] = find(P7);

    % shifting
    j2 = j2 + ni(1);

    i3 = i3 + mi(1);

    i4 = i4 + mi(1);
    j4 = j4 + ni(1);

    i5 = i5 + mi(1);
    j5 = j5 + c(3)-1;

    i6 = i6 + r(3)-1;
    j6 = j6 + ni(1);

    i7 = i7 + r(3)-1;
    j7 = j7 + c(3)-1;

    % computes the 7 separate parts as sparse matrices of size m,n such
    % that they can be spied all together in the same figure
    
    A1 = sparse(i1,j1,ones(size(i1)),m,n);
    A2 = sparse(i2,j2,ones(size(i2)),m,n);
    A3 = sparse(i3,j3,ones(size(i3)),m,n);
    A4 = sparse(i4,j4,ones(size(i4)),m,n);
    A5 = sparse(i5,j5,ones(size(i5)),m,n);
    A6 = sparse(i6,j6,ones(size(i6)),m,n);
    A7 = sparse(i7,j7,ones(size(i7)),m,n);

    figure; hold on;
    spy(A1,'r');
    spy(A2,'g');
    spy(A3,'b');
    spy(A4,'c');
    spy(A5,'m');
    spy(A6,'y');
    spy(A7,'k');
    hold off;
