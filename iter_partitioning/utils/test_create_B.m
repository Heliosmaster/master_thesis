close all; clc; clear all;
matrix = '../../matrices/m_testbed/dfl001.mtx';
%str = ['matrices/' matrix '.mtx'];
A = mmread(matrix);
[m,n] = size(A);
Ar = double((A==1));
Ac = double((A==2));
B = create_B(Ar,Ac,m,n);
B1 = MatlabCreateB(Ac,Ar);