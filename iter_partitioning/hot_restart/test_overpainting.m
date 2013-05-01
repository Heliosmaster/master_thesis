clear all; close all; clc;
%A = mmread('/home/students/3776123/mthesis/matrices/test_matrix.mtx');
% A = mmread('/home/davide/projects/mthesis/matrices/test_matrix.mtx');
 A = mmread('/home/davide/projects/mthesis/matrices/tbdlinux.mtx');
%[v,l] = pa_sort_mix(A,0);
[v,l] = pa_random(A);
%v = [3 4 11 12 16 6 2 7 15 14 9 8 10 1 13 17 18 5];
[Ac1,Ar1] = MatlabOverpaint(A,v);
%[Ac,Ar] = overpainting(A,v);
