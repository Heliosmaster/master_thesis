%close all; clc; clear all;
matrix = 'test_matrix';
str = ['matrices/' matrix '.mtx'];
A = mmread(str);
[m,n] = size(A);
Ar = double((A==1));
Ac = double((A==2));
B = create_B(Ar,Ac,m,n);
B1 = MatlabCreateB(Ac,Ar);