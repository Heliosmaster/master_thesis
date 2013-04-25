clear all; close all; clc;
A = mmread('/home/students/3776123/mthesis/matrices/dfl001.mtx');
[v,l] = pa_sort_mix(A,0);
[Ac,Ar] = overpainting(A,v);
