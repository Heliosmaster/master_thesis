function [Ar,Ac]=super_sbdview(I,p,q,r,c)
[m,n] = size(I);

% computes the size of the blocks
mi = [r(2)-r(1),r(3)-r(2),r(4)-r(3),r(5)-r(4),r(6)-r(5)];
ni = [c(2)-c(1),c(3)-c(2),c(4)-c(3),c(5)-c(4),c(6)-c(5)];

% initialization of the vectors for Ar and Ac
ir = [];
jr = [];
ic = [];
jc = [];

%split I into the 7 parts of the SBD
[P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13] = supersplit_subparts(I,p,q,r,c);
%
num_nz = zeros(13,1);
num_nz(1) = nnz(P1);
num_nz(2) = nnz(P2);
num_nz(3) = nnz(P3);
num_nz(4) = nnz(P4);
num_nz(5) = nnz(P5);
num_nz(6) = nnz(P6);
num_nz(7) = nnz(P7);
num_nz(8) = nnz(P8);
num_nz(9) = nnz(P9);
num_nz(10) = nnz(P10);
num_nz(11) = nnz(P11);
num_nz(12) = nnz(P12);
num_nz(13) = nnz(P13);


% converting to vectors
[i1,j1,~] = find(P1);
[i2,j2,~] = find(P2);
[i3,j3,~] = find(P3);
[i4,j4,~] = find(P4);
[i5,j5,~] = find(P5);
[i6,j6,~] = find(P6);
%[i7,j7,~] = find(P7);
[i8,j8,~] = find(P8);
[i9,j9,~] = find(P9);
[i10,j10,~] = find(P10);
[i11,j11,~] = find(P11);
[i12,j12,~] = find(P12);
[i13,j13,~] = find(P13);

i1 = i1(:);
i2 = i2(:);
i3 = i3(:);
i4 = i4(:);
i5 = i5(:);
i6 = i6(:);
i8 = i8(:);
i9 = i9(:);
i10 = i10(:);
i11 = i11(:);
i12 = i12(:);
i13 = i13(:);

j1 = j1(:);
j2 = j2(:);
j3 = j3(:);
j4 = j4(:);
j5 = j5(:);
j6 = j6(:);
j8 = j8(:);
j9 = j9(:);
j10 = j10(:);
j11 = j11(:);
j12 = j12(:);
j13 = j13(:);

% shifting
j2 = j2 + ni(1);

i3 = i3 + mi(1);

i4 = i4 + mi(1);
j4 = j4 + ni(1);

i5 = i5 + mi(1);
j5 = j5 + c(3)-1;

i6 = i6 + r(3)-1;
j6 = j6 + ni(1);

%i7 = i7 + r(3)-1;
%j7 = j7 + c(3)-1;

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

%P1 - P13
ir = [ir; i1];
jr = [jr; j1];

%P2
ir = [ir; i2];
jr = [jr; j2];

%P3

ic = [ic; i3];
jc = [jc; j3];

%P4
if mi(2) > ni(2)
    ir = [ir; i4];
    jr = [jr; j4];
else
    ic = [ic; i4];
    jc = [jc; j4];
end

%P5

ir = [ir; i5];
jr = [jr; j5];


ic = [ic; i6];
jc = [jc; j6];


%P7
[Ac7,Ar7] = localview(P7);
[ir7,jr7,~] = find(Ar7);
[ic7,jc7,~] = find(Ac7);

ir7 = ir7 + r(3)-1;
ic7 = ic7 + r(3)-1;
jr7 = jr7 + c(3)-1;
jc7 = jc7 + c(3)-1;

ir = [ir; ir7];
jr = [jr; jr7];
ic = [ic; ic7];
jc = [jc; jc7];

ic = [ic; i8];
jc = [jc; j8];

%P9
ir = [ir; i9];
jr = [jr; j9];

%P10
if mi(4) > ni(4)
    ir = [ir; i10];
    jr = [jr; j10];
else
    ic = [ic; i10];
    jc = [jc; j10];
end

%P11

ic = [ic; i11];
jc = [jc; j11];

%P12

ir = [ir; i12];
jr = [jr; j12];

%P13
ic = [ic; i13];
jc = [jc; j13];


% computes the inverse of p,q in order to give the matrix in regular form
p1 = reverse_perm(p);
q1 = reverse_perm(q);

% computes Ar,Ac in SBD form and regularize it
Ar = sparse(ir,jr,ones(size(ir)),m,n);
Ar = Ar(p1,q1);
Ac = sparse(ic,jc,ones(size(ic)),m,n);
Ac = Ac(p1,q1);
end