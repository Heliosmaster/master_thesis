close all; clc; clear all;
matrix = '../../matrices/m_testbed/tbdlinux.mtx';
%matrix = '../../matrices/new_testbed/tbdmatlab.mtx';
%matrix = '../../matrices/test_matrix.mtx';
A = mmread(matrix);
for i=1:100
    B = MatlabToMondriaanToMatlab(A);
end