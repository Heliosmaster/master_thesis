%clear all; close all;
matrix = 'dfl001';
str = ['matrices/' matrix '.mtx'];
%A = mmread(str);
A = sprand(30,30,0.3);
clear str
[I, s, p, q, r, c, rh, ch, B, u, v] = mondriaanplot(A,2,0.03,0,0,-1,1);
figure(2);
mondriaanplot(A,2,0.03,0,0,-1,5);
