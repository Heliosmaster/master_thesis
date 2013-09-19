%clear all; close all; clc;

printIteration = 0;
% read the input sparse matrix
strdir = '../all2/';
d = dir([strdir '*.mtx']);
%d = dir('../matrices/new_testbed/*.mtx');

for k=1:length(d)
		 matrix = d(k).name;
		 %strdir = '../matrices2/';
		 %matrix = 'nug30';
		 str = [strdir matrix ];
		 A = mmread(str);

		 clear str

		 %iteration number
		 outeriter = 20;
		 inneriter = 5;
		 iter = 2;
		 flag = 0;
		 i=1;
		 results = zeros(1,inneriter);
		 times = zeros(1,inneriter);
		 total_initials = zeros(1,outeriter);
		 total_means = zeros(1,outeriter);
		 total_times = zeros(1,outeriter);

		 fprintf('\n%s - %g\n\n',matrix,flag);

		 counter = 0;


		 tStart = tic;

		 %initial split (8 = twodim)
		 for z=1:outeriter
				[I, s, ~, ~ , ~, ~, ~, ~, ~, ~, ~] = mondriaan(A,2,0.03,2,0,8);
				%results(1) = s(4);
				[m,n] = size(A);      

				fprintf('localview_%g:\t ',flag);

				fprintf('%g | ',s(4));
				total_initials(z)=s(4);

				for j=1:inneriter
						innerStart = tic;         
						[Ac,Ar] = MatlabLocalview(I,flag);
						%					for i=2:iter
						B = MatlabCreateB(Ac,Ar);
						[I2, s, ~, ~, ~, ~, ~, ~, ~, ~, ~] = mondriaan(B,2,0.03,0,0,5);
						fprintf('%5g ',s(4));
						%							Ar2 = I2(1:n,n+1:end)';
						%							Ac2 = I2(n+1:end,1:n);        
						%							A2 = Ar2+Ac2;	
						%							[Ac,Ar] = MatlabLocalview(A2,flag);
						%						end
						results(j) = s(4);
						elapsedTime = toc(innerStart);
						% fprintf('\t time %g s',elapsedTime); % (avg %5.2f
						times(j) = elapsedTime;
						% fprintf('\n');
				end
				total_means(z) = mean(results);
				total_times(z) = mean(times);
				fprintf('\t avg: %g\t %g s\n',total_means(z),total_times(z));
	 end
	 fprintf('------\n');
	 totalTime = toc(tStart);
	 fprintf('mean initials %g, mean final %g, time %g s (mean %g s)\n',mean(total_initials),mean(total_means),totalTime,mean(total_times));
 end
