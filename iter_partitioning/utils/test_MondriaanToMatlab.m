close all; clc; clear all;
%matrix = '../../matrices/m_testbed/tbdlinux.mtx';
%matrix = '../../matrices/test_matrix.mtx';
%A = mmread(matrix);
for i=1:10000
    A = MondriaanToMatlab;
end