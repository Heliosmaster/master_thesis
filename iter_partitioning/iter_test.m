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
    iter = 4;
    i=1;
    results = zeros(1,iter);

    fprintf('\n%s\n\n',matrix);

    %initial split (8 = twodim)
    for z=1:5
        [I, s, ~, ~ , ~, ~, ~, ~, ~, ~, ~] = mondriaan(A,2,0.03,2,0,8);
        results(1) = s(4);
        %separating the two parts as S1 and S2
        [m,n] = size(A);



        %%%%%%%%%%%%%%%%%%%%%%%% PA

        %%%%%%%%%%% pa-unsorted

        for j=1:5
            fprintf('pa-unsorted-simple-row:\t\t ');
            tic;
            v = pa_simple(I,'row');
            fprintf('%g ',results(1)); [Ac,Ar] = MatlabOverpaint(I,v);
            for i=2:iter
               inner_loop;
               v = pa_simple(A2,'row');
               [Ac,Ar] = MatlabOverpaint(A2,v);
            end
            elapsedTime = toc;
            fprintf('\t (avg %5.2f time %g s)',mean(results),elapsedTime);
            fprintf('\n');
        end
    end
    
    fprintf('------\n');
    
   
end
