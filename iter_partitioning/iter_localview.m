%clear all; close all; clc;

printIteration = 0;
% read the input sparse matrix
strdir = '../matrices/m_testbed/';
d = dir([strdir '*.mtx']);
%d = dir('../matrices/new_testbed/*.mtx');

for k=1:length(d)
    matrix = d(k).name;
    str = [strdir matrix];
    A = mmread(str);

    clear str

    %iteration number
    outeriter = 20;
    inneriter = 5;
    iter = 2;
    i=1;
    results = zeros(1,iter);
    total_initials = zeros(1,outeriter);
    total_means = zeros(1,outeriter*inneriter);
    total_times = zeros(1,outeriter*inneriter);

    fprintf('\n%s\n\n',matrix);
    
    counter = 0;
    
    tStart = tic;

    %initial split (8 = twodim)
    for z=1:outeriter
        [I, s, ~, ~ , ~, ~, ~, ~, ~, ~, ~] = mondriaan(A,2,0.03,2,0,8);
        results(1) = s(4);
        %separating the two parts as S1 and S2
        [m,n] = size(A);      
       
        
        fprintf(['localview:\t ']);
                       
        fprintf('%g | ',results(1));
        total_initials(z)=results(1);

        %%%%%%%%%%%%%%%%%%%%%%%% PA
        %%%%%%%%%%% pa-unsorted

        for j=1:inneriter
            counter = counter+1;
            innerStart = tic;         
            [Ac,Ar] = MatlabLocalview(A);
            for i=2:iter
                inner_loop;
                [Ac,Ar] = MatlabLocalview(A2);
            end
            elapsedTime = toc(innerStart);
           % fprintf('\t time %g s',elapsedTime); % (avg %5.2f
            total_means(counter) = min(results);
            total_times(counter) = elapsedTime;
           % fprintf('\n');
        end
           fprintf('\n');
    end
    fprintf('------\n');
    totalTime = toc(tStart);
    fprintf('mean initials %g, mean final %g, time %g s (mean %g s)\n',mean(total_initials),mean(total_means),totalTime,mean(total_times));
end
