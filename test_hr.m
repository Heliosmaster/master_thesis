close all; clc; clear all;
matrix = 'test_matrix';
str = ['matrices/' matrix '.mtx'];
A = mmread(str);
[m,n] = size(A);
hot_restart