%close all; clc; clear all;
cd ..
startup
cd utils
matrix = '../../matrices/big_matrices/tbdlinux.mtx';
A = mmread(matrix);
[m,n] = size(A);
for i=1:100
    clear B
    B = MatlabConvert(A);
end
