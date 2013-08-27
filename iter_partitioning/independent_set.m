function v=independent_set(matrix,I,flag)
[uncut,cut]=uncut_before_cut(I);
%dlmwrite('matlab_temp.txt',uncut,'\n');
is1 = wrapper_is(matrix,uncut);
if (flag==1)
	v=[is1,setdiff(uncut,is1),cut];
end
if (flag==2)
	is2 = wrapper_is(matrix,cut);
	v=[is1,setdiff(uncut,is1),is2,setdiff(cut,is2)];
end
if (flag==3)
	set3 = [setdiff(uncut,is1) cut];
	is3 = wrapper_is(matrix,set3);
	v = [is1,is3,setdiff(set3,is3)];
end
