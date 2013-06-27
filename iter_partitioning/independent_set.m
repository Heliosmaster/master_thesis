function v=independent_set(matrix,I)
[uncut,cut]=uncut_before_cut(I);
dlmwrite('matlab_temp.txt',uncut,'\n');
python_cmd = ['python maximum_independent_set.py ' matrix];
unix(python_cmd);
delete('matlab_temp.txt');
is = dlmread([matrix '.set'])';
delete([matrix '.set']);
v=[is setdiff(uncut,is),cut];