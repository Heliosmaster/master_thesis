%close all; clc; clear all;
matrix = 'nug30';
str = ['../old_matrices/' matrix '.mtx'];
A = mmread(str);

clear str

%iteration number
outeriter = 20;
iter = 0;
i=1;
results = zeros(1,iter);
values = zeros(1,outeriter);
initials = zeros(1,outeriter);
fprintf('\n%s\n\n',matrix);

counter = 0;

tStart = tic;

%initial split (8 = twodim)
for j=1:outeriter
	[I, s, ~, ~ , ~, ~, ~, ~, ~, ~, ~] = mondriaan(A,2,0.03,2,0,8);
	results(1) = s(4);
	[m,n] = size(A);
	fprintf('po_unsorted_concat:\t ');
	fprintf('%5.2f | ',results(1));
	initials(j) = s(4);
	%v = po_unsorted_concat(I,'col');
	%[Ac,Ar] = MatlabOverpaint(I,v);
	for i=2:iter+1
    inner_loop;
    results(i-1) = s(4);
    v = po_unsorted_concat(A2,'col');
  	[Ac,Ar] = MatlabOverpaint(A2,v);
	end
	values(j) = mean(results);
	fprintf(' avg: \t %5.2f',values(j));
	fprintf('\n');
end
fprintf('--------------------\n');
fprintf('avg initials: %5.2f \t\t avg finals: %5.2f\n',mean(initials),mean(values));
