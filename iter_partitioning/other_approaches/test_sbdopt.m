clear all; close all; clc;
matrix = 'tbdmatlab';
str = ['../old_matrices/' matrix '.mtx'];
A = mmread(str);
[m,n]= size(A);
clear str matrix;

% %iteration number
% %initial split (8 = twodim)
[I, s, pu, qu, ru, cu, rh, ch, B, u, v] = mondriaan(A,2,0.03,2,0,8);
[p,q,r,c] = sbdopt(I);
%sbd_plot(I,p,q,r,c);
%[Ar,Ac]=sbdview(I,p,q,r,c);
%figure;
[p,q,r,c] = sbd(I);
%sbd_plot(I,p,q,r,c);

%spy(Ar,'r'); hold on; spy(Ac,'g');
