close all; clc; clear all;
matrix = 'tbdlinux';
str = ['../../matrices/' matrix '.mtx'];
A = mmread(str);
[Ac,Ar]=localview(A);
[Ac1,Ar1]=MatlabLocalview(A);