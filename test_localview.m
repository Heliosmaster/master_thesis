close all;
matrix = 'test_matrix';
str = ['matrices/' matrix '.mtx'];
A = mmread(str);
[Ac,Ar]=localview(A);
Ac
Ar