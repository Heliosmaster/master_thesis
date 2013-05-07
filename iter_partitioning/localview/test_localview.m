close all; clc; clear all;
matrix = 'tbdlinux';
str = ['../../matrices/m_testbed/' matrix '.mtx'];
A = mmread(str);
[Ac,Ar]=localview(A);
[Ac1,Ar1]=MatlabLocalview(A);