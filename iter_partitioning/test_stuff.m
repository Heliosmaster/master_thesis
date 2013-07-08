close all; clc; clear all;
str = ['../matrices/m_testbed/tbdmatlab.mtx'];
%str = ['../matrices/test_matrix.mtx'];
A = mmread(str);
[I, s, ~, ~ , ~, ~, ~, ~, ~, ~, ~] = mondriaan(A,2,0.03,2,0,4);
fprintf('col net: %g\n',s(4));
[I, s, ~, ~ , ~, ~, ~, ~, ~, ~, ~] = mondriaan(A,2,0.03,2,0,5);
fprintf('row net: %g\n',s(4));
% 
[m,n] = size(A);
% 
% Ar = A;
% Ac = sparse(m,n);
% B = MatlabCreateB(Ac,Ar);
% [I, s, ~, ~ , ~, ~, ~, ~, ~, ~, ~] = mondriaan(B,2,0.03,2,0,5);
% fprintf('All in Ar: %g\n',s(4));
% 
% Ac = A;
% Ar = sparse(m,n);
% B = MatlabCreateB(Ac,Ar);
% [I, s, ~, ~ , ~, ~, ~, ~, ~, ~, ~] = mondriaan(B,2,0.03,2,0,5);
% fprintf('All in Ac: %g\n',s(4));
% 
v = po_unsorted_concat(A,'row');
[Ac1,Ar1] = MatlabOverpaint(A,v);
B = MatlabCreateB(Ac1,Ar1);
[I2, s, ~, ~, ~, ~, ~, ~, ~, ~, ~] = mondriaan(B,2,0.03,0,0,5);
fprintf('Overpaint Ar: %g\n',s(4));

v = po_unsorted_concat(A,'col');
[Ac2,Ar2] = MatlabOverpaint(A,v);
B = MatlabCreateB(Ac2,Ar2);
[I2, s, ~, ~, ~, ~, ~, ~, ~, ~, ~] = mondriaan(B,2,0.03,0,0,5);
fprintf('Overpaint Ac: %g\n',s(4));