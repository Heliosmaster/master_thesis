% supersbd_plot(I,p,q,r,c)
%
% given [p,q,r,c]=super_sbd(I) prints a figure with all the 13 blocks of the SBD
% form in a different color
% note: shares code with sbdview
function supersbd_plot(I,p,q,r,c)
    [m,n] = size(I);
    [P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13] = supersplit_subparts(I,p,q,r,c);

    % computes the size of the blocks
    mi = [r(2)-r(1),r(3)-r(2),r(4)-r(3),r(5)-r(4),r(6)-r(5)];
    ni = [c(2)-c(1),c(3)-c(2),c(4)-c(3),c(5)-c(4),c(6)-c(5)];
    
    % converting to vectors
    [i1,j1,~] = find(P1);
    [i2,j2,~] = find(P2);
    [i3,j3,~] = find(P3);
    [i4,j4,~] = find(P4);
    [i5,j5,~] = find(P5);
    [i6,j6,~] = find(P6);
    [i7,j7,~] = find(P7);
    [i8,j8,~] = find(P8);
    [i9,j9,~] = find(P9);
    [i10,j10,~] = find(P10);
    [i11,j11,~] = find(P11);
    [i12,j12,~] = find(P12);
    [i13,j13,~] = find(P13);

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
    
    i8 = i8 + r(3)-1;
    j8 = j8 + c(4)-1;
    
    i9 = i9 + r(4)-1;
    j9 = j9 + c(3)-1;
    
    i10 = i10 + r(4)-1;
    j10 = j10 + c(4)-1;
    
    i11 = i11 + r(4)-1;
    j11 = j11 + c(5)-1;
    
    i12 = i12 + r(5)-1;
    j12 = j12 + c(4)-1;
    
    i13 = i13 + r(5)-1;
    j13 = j13 + c(5)-1;

    % computes the 13 separate parts as sparse matrices of size m,n such
    % that they can be spied all together in the same figure
    
    A1 = sparse(i1,j1,ones(size(i1)),m,n);
    A2 = sparse(i2,j2,ones(size(i2)),m,n);
    A3 = sparse(i3,j3,ones(size(i3)),m,n);
    A4 = sparse(i4,j4,ones(size(i4)),m,n);
    A5 = sparse(i5,j5,ones(size(i5)),m,n);
    A6 = sparse(i6,j6,ones(size(i6)),m,n);
    A7 = sparse(i7,j7,ones(size(i7)),m,n);
    A8 = sparse(i8,j8,ones(size(i8)),m,n);
    A9 = sparse(i9,j9,ones(size(i9)),m,n);
    A10 = sparse(i10,j10,ones(size(i10)),m,n);
    A11 = sparse(i11,j11,ones(size(i11)),m,n);
    A12 = sparse(i12,j12,ones(size(i12)),m,n);
    A13 = sparse(i13,j13,ones(size(i13)),m,n);

    figure; hold on;
    spy(A1,'r');
    spy(A2,'g');
    spy(A3,'b');
    spy(A4,'c');
    spy(A5,'m');
    spy(A6,'y');
    spy(A7,'k');
    spy(A8,'r');
    spy(A9,'g');
    spy(A10,'b');
    spy(A11,'c');
    spy(A12,'m');
    spy(A13,'y');
    hold off;
