%close all; clc; clear all;
strdir = '../matrices_preliminary/';
d = dir([strdir '*.mtx']);

for k=1:length(d)
	matrix = d(k).name;
	%matrix = 'tbdlinux';
	str = [strdir matrix ];
	%str = [str '.mtx'];
	A  = mmread(str);


	clear str

	%iteration number
	outeriter = 10;
	iter = 10;
	flag = 1; % 0 = partition oblivious, 1 = partition aware
	i=1;
	results = zeros(1,iter);
	values = zeros(outeriter,iter+1);
	fprintf('\n%s\n\n',matrix);

	counter = 0;

	tStart = tic;

	%initial split (8 = twodim)
	for j=1:outeriter
		[I, s, ~, ~ , ~, ~, ~, ~, ~, ~, ~] = mondriaan(A,2,0.03,2,0,8);
		[m,n] = size(A);
		fprintf('pa_sorted_w_simple:\t ');
		fprintf('%4g | ',s(4));

		values(j,1) = s(4);
		v = pa_sorted_simple(I,1);
		[Ac,Ar] = MatlabOverpaint(I,v);

		for i=2:iter+1
			inner_loop;
			values(j,i) = s(4);
			v = pa_sorted_simple(A2,1);
			[Ac,Ar] = MatlabOverpaint(A2,v);
end
fprintf('\n');
end
fprintf('--------------------\n');
fprintf('\t\t');
fprintf('%5g | ',mean(values(:,1)));
for i=2:iter+1
		fprintf('%5g ',mean(values(:,i)));
end
fprintf('\n');
% fprintf('\t time %g s',elapsedTime); % (avg %5.2f
% fprintf('\n');
end
