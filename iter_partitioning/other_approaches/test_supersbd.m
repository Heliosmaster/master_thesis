clear all; close all; clc;

% read the input sparse matrix
%matrix = 'dfl001';
matrix = 'cage7';
%matrix = 'impcol_b';
%matrix = 'sherman1';
str = ['../../matrices/testbed2/' matrix '.mtx'];
A = mmread(str);
%A = sprand(30,30,0.3);
[m,n]= size(A);
clear str matrix;

% %iteration number
% %initial split (8 = twodim)
[I, s, pu, qu, ru, cu, rh, ch, B, u, v] = mondriaan(A,2,0.03,2,0,8);
% super_sbd;
[p,q,r,c] = super_sbd(I);
% figure; spy(I(p,q));
supersbd_plot(I,p,q,r,c);


[Ar,Ac]=super_sbdview(I,p,q,r,c);
 
figure;
spy(Ar,'r'); hold on; spy(Ac,'g');
