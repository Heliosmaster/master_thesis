function is=wrapper_is(matrix,set)
fid = fopen('matlab_temp.txt','w');
for i=1:size(set,2)
  fprintf(fid,'%g\n',set(i));
end
fclose(fid);
python_cmd = ['python maximum_independent_set.py ' matrix ' 1'];
unix(python_cmd);
delete('matlab_temp.txt');
setfile = [matrix '.set'];
is = dlmread(setfile)';
delete(setfile);
