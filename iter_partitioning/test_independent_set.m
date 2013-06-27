clear all; clc;
matrix = '../matrices/m_testbed/tbdmatlab.mtx'; 
A = mmread(matrix);
[I, s, ~, ~ , ~, ~, ~, ~, ~, ~, ~] = mondriaan(A,2,0.03,2,0,8);
v=independent_set(matrix,I);
