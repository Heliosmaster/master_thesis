%clear all; close all; clc;

printIteration = 0;
% read the input sparse matrix
strdir = '../matrices_preliminary/';
d = dir([strdir '*.mtx']);

for k=1:length(d)
		 matrix = d(k).name;
%		 matrix = 'dfl001';
		 str = [strdir matrix ];
 %        str = [str '.mtx'];
		 A = mmread(str);

		 clear str

		 %iteration number
		 outeriter = 20;
		 inneriter = 5;
		 iter = 2;
		 flag = 1;
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

				fprintf(['sbd2view:\t ']);

				fprintf('%g | ',s(4));
				total_initials(z)=s(4);

				for j=1:inneriter
						innerStart = tic;         
						[p,q,r,c] = sbd2opt(I); [Ac,Ar] = super_sbdview(I,p,q,r,c);
	%					[Ac,Ar] = MatlabLocalview(I,flag);
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
				fprintf('\t avg: %5.2f\t %5.2f s\n',total_means(z),total_times(z));
	 end
	 fprintf('------\n');
	 totalTime = toc(tStart);
	 fprintf('mean initials %5.2f, mean final %5.2f, time %g s (mean %g s)\n',mean(total_initials),mean(total_means),totalTime,mean(total_times));
end
