function is=wrapper_is(matrix,set,id)
strtmp = ['matlab_temp' id '.txt'];
fid = fopen(strtmp,'w');
for i=1:size(set,2)
  fprintf(fid,'%u\n',set(i));
end
fclose(fid);
python_cmd = ['python maximum_independent_set.py ' matrix ' ' strtmp];
unix(python_cmd);
delete(strtmp);
setfile = [matrix '.set'];
is = dlmread(setfile)';
delete(setfile);
