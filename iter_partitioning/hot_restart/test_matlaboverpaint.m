clear all; close all; clc;
A = mmread('../../matrices/test_matrix.mtx');
[m,n] = size(A);
v = po_simple(A,'row');
[Ac,Ar] = MatlabOverpaint(A,v);
%Ac = A;
%Ar = sparse(m,n);
%for i=1:100
%     [I, s, ~, ~ , ~, ~, ~, ~, ~, ~, ~] = mondriaan(A,2,0.03,2,0,8);
%     disp(s(4));
%    A = MatlabCreateB(Ac,Ar);
%end