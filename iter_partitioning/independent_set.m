function v=independent_set(matrix,I,flag,id)
if (flag==0)
	[m,n] = size(I);
	set1 = 1:m+n;
	is1 = wrapper_is(matrix,set1,id);
	v = [is1,setdiff(set1,is1)];
else
	[uncut,cut]=uncut_before_cut(I);
	%dlmwrite('matlab_temp.txt',uncut,'\n');
	is1 = wrapper_is(matrix,uncut,id);
	if (flag==1)
		v=[is1,setdiff(uncut,is1),cut];
	end
	if (flag==2)
		is2 = wrapper_is(matrix,cut,id);
		v=[is1,setdiff(uncut,is1),is2,setdiff(cut,is2)];
	end
	if (flag==3)
		set3 = [setdiff(uncut,is1) cut];
		is3 = wrapper_is(matrix,set3,id);
		v = [is1,is3,setdiff(set3,is3)];
	end
end
