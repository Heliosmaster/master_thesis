clear all; close all; clc;
A = mmread('/home/davide/projects/mthesis/matrices/dfl001.mtx');
[v,l] = pa_sort_mix(A,0);
[Ac,Ar] = overpainting(A,v);