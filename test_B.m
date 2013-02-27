close all;
matrix = 'impcol_b';
str = ['matrices/' matrix '.mtx'];
A = mmread(str);
[I, s, p, q, r, c, rh, ch, B, u, v] = mondriaan(A,2,0.03,0,0,8);
%separating the two parts as S1 and S2
[m,n] = size(A);
[i1,j1,s1] = find(I==1);
Ar = sparse(i1,j1,s1,m,n);
[i2,j2,s2] = find(I==2);
Ac = sparse(i2,j2,s2,m,n);

B = create_B(Ar,Ac,m,n);

% test_mat;
% [m,n] = size(A);
% [i1,j1,s1] = find(A==1);
% Ar = sparse(i1,j1,s1,m,n);
% [i2,j2,s2] = find(A==2);
% Ac = sparse(i2,j2,s2,m,n);
% B = create_B(Ar,Ac,m,n);
spy(B);
B=globalview(B,m,n);
figure; spy(B);