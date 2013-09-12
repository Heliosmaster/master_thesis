format long g;
%close all; clc; clear all;
%matrix = 'dfl001';
%str = ['../matrices_preliminary/' matrix '.mtx'];
strdir = '../matrices4/';
%d = dir([strdir '*.mtx']);

%for k=1:length(d)
	%matrix = d(k).name;
	matrix = 'italy_osm';
	str = [strdir matrix ];
	str = [str '.mtx'];
	A  = mmread(str);

	%clear str
	for flag=[0,1,3]
		%iteration number
		outeriter = 20;
		iter = 5;
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
			[m,n] = size(A);
			fprintf('is_%g:\t ',flag);
			fprintf('%5g | ',s(4));
			initials(j) = s(4);
			for i=1:iter
				v = independent_set(str,I,flag);
				[Ac,Ar] = MatlabOverpaint(I,v);
				B = MatlabCreateB(Ac,Ar);
				[I2, s, ~, ~ , ~, ~, ~, ~, ~, ~, ~] = mondriaan(B,2,0.03,0,0,5);
				results(i) = s(4);
				fprintf('%5g ',s(4));
		end
		values(j) = mean(results);
		fprintf(' avg: \t %5g',values(j));
		fprintf('\n');
	end
	fprintf('--------------------\n');
	fprintf('avg initials: %5g \t\t avg finals: %5g\n\n\n',mean(initials),mean(values));
end
%end
