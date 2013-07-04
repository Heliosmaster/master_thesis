function v=independent_set(matrix,I)
[uncut,cut]=uncut_before_cut(I);
%dlmwrite('matlab_temp.txt',uncut,'\n');
fid = fopen('matlab_temp.txt','w');
for i=1:size(uncut,2)
  fprintf(fid,'%g\n',uncut(i));
end
fclose(fid);
python_cmd = ['python maximum_independent_set.py ' matrix];
unix(python_cmd);
delete('matlab_temp.txt');
is = dlmread([matrix '.set'])';
delete([matrix '.set']);
v=[is setdiff(uncut,is),cut];