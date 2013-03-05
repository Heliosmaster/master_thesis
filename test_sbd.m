clear all; close all; clc;

% read the input sparse matrix
% matrix = 'impcol_b';
matrix = 'cage6';
str = ['matrices/' matrix '.mtx'];
A = mmread(str);
%A = sprand(30,30,0.3);
[m,n]= size(A);
clear str

%iteration number
%initial split (8 = twodim)
[I, s, p, q, r, c, rh, ch, B, u, v] = mondriaan(A,2,0.03,2,0,1);

spy(I(p,q)); 
[Ar,Ac]=sbdview(I,p,q,r,c);

figure;
 spy(Ar,'r'); hold on; spy(Ac,'g');