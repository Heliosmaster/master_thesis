%close all; clc; clear all;
%matrix = 'dfl001';
%str = ['../matrices_preliminary/' matrix '.mtx'];
strdir = '../old_matrices/';
%d = dir([strdir '*.mtx']);

%for k=1:length(d)
%matrix = d(k).name;
matrix = 'tbdmatlab';
str = [strdir matrix ];
str = [str '.mtx'];
A  = mmread(str);

%clear str
for flag=1:3
%iteration number
outeriter = 1;
iter = 2;
i=1;
results = zeros(1,iter);
values = zeros(1,outeriter);
initials = zeros(1,outeriter);
fprintf('\n%s - %g\n\n',matrix,flag);

counter = 0;

tStart = tic;

%initial split (8 = twodim)
for j=1:outeriter
		[I, s, ~, ~ , ~, ~, ~, ~, ~, ~, ~] = mondriaan(A,2,0.03,0,0,8);
		results(1) = s(4);
		[m,n] = size(A);
		fprintf('is_%g:\t ',flag);
		fprintf('%5.2f | ',results(1));
		initials(j) = s(4);
		v = independent_set(str,I,flag);
		[Ac,Ar] = MatlabOverpaint(I,v);
		for i=2:iter+1
			inner_loop;
			results(i-1) = s(4);
			v = independent_set(str,A2,flag);
			[Ac,Ar] = MatlabOverpaint(A2,v);
	end
	values(j) = mean(results);
	fprintf(' avg: \t %5.2f',values(j));
	fprintf('\n');
end
fprintf('--------------------\n');
fprintf('avg initials: %5.2f \t\t avg finals: %5.2f\n',mean(initials),mean(values));
end
%end
