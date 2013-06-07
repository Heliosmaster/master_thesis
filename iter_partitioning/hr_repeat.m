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
    iter = 2;
    i=1;
    results = zeros(1,iter);

    fprintf('\n%s\n\n',matrix);

    %initial split (8 = twodim)
    [I, s, ~, ~ , ~, ~, ~, ~, ~, ~, ~] = mondriaan(A,2,0.03,2,0,8);
    results(1) = s(4);
    %separating the two parts as S1 and S2
    [m,n] = size(A);
    
    outer_iter = 2;
    avg_outer = zeros(1,outer_iter);

    
    %%%%%%%%%%%%%%%%%%%%%%%% PA
    
    %%%%%%%%%%% pa-sort-nw
    
    for j=1:outer_iter
        fprintf('pa-sorted-nw-simple:\t\t ');
        tic;
        v = pa_sorted_simple(I,0);
        fprintf('%g ',results(1)); [Ac,Ar] = MatlabOverpaint(I,v);
        for i=2:iter
           inner_loop;
          v = pa_sorted_simple(A2,0);
           [Ac,Ar] = MatlabOverpaint(A2,v);
        end
        elapsedTime = toc;
        fprintf('\t (avg %5.2f time %g s)',mean(results),elapsedTime);
        avg_outer(j) = mean(results);
        fprintf('\n');
    end
    fprintf('average value over %g iterations is %5.2f\n\n\n',outer_iter,mean(avg_outer));
    
    for j=1:outer_iter
        fprintf('pa-sorted-nw-random:\t\t ');
        tic;
        v = pa_sorted_random(I,0);
        fprintf('%g ',results(1)); [Ac,Ar] = MatlabOverpaint(I,v);
        for i=2:iter
           inner_loop;
           v = pa_sorted_random(A2,0);
           [Ac,Ar] = MatlabOverpaint(A2,v);
        end
        elapsedTime = toc;
        fprintf('\t (avg %5.2f time %g s)',mean(results),elapsedTime);
        avg_outer(j) = mean(results);
        fprintf('\n');
    end
    fprintf('average value over %g iterations is %5.2f\n\n\n',outer_iter,mean(avg_outer));
    
    for j=1:outer_iter
        fprintf('pa-sorted-nw-mix-alt-row:\t ');
        tic;
        v = pa_sorted_mix(I,0,0,0);
        fprintf('%g ',results(1)); [Ac,Ar] = MatlabOverpaint(I,v);
        for i=2:iter
           inner_loop;
           v = pa_sorted_mix(A2,0,0,0);
           [Ac,Ar] = MatlabOverpaint(A2,v);
        end
        elapsedTime = toc;
        fprintf('\t (avg %5.2f time %g s)',mean(results),elapsedTime);
        avg_outer(j) = mean(results);
        fprintf('\n');
    end
    fprintf('average value over %g iterations is %5.2f\n\n\n',outer_iter,mean(avg_outer));
    
    for j=1:outer_iter
        fprintf('pa-sorted-nw-mix-alt-col:\t ');
        tic;
        v = pa_sorted_mix(I,0,0,1);
        fprintf('%g ',results(1)); [Ac,Ar] = MatlabOverpaint(I,v);
        for i=2:iter
           inner_loop;
           v = pa_sorted_mix(A2,0,0,1);
           [Ac,Ar] = MatlabOverpaint(A2,v);
        end
        elapsedTime = toc;
        fprintf('\t (avg %5.2f time %g s)',mean(results),elapsedTime);
        avg_outer(j) = mean(results);
        fprintf('\n');
    end
    fprintf('average value over %g iterations is %5.2f\n\n\n',outer_iter,mean(avg_outer));
    
    for j=1:outer_iter
        fprintf('pa-sorted-nw-mix-spr-row:\t ');
        tic;
        v = pa_sorted_mix(I,0,1,0);
        fprintf('%g ',results(1)); [Ac,Ar] = MatlabOverpaint(I,v);
        for i=2:iter
           inner_loop;
           v = pa_sorted_mix(A2,0,1,0);
           [Ac,Ar] = MatlabOverpaint(A2,v);
        end
        elapsedTime = toc;
        fprintf('\t (avg %5.2f time %g s)',mean(results),elapsedTime);
        avg_outer(j) = mean(results);
        fprintf('\n');
    end
    fprintf('average value over %g iterations is %5.2f\n\n\n',outer_iter,mean(avg_outer));
    
    for j=1:outer_iter
        fprintf('pa-sorted-nw-mix-spr-col:\t ');
        tic;
        v = pa_sorted_mix(I,0,1,1);
        fprintf('%g ',results(1)); [Ac,Ar] = MatlabOverpaint(I,v);
        for i=2:iter
           inner_loop;
           v = pa_sorted_mix(A2,0,1,1);
           [Ac,Ar] = MatlabOverpaint(A2,v);
        end
        elapsedTime = toc;
        fprintf('\t (avg %5.2f time %g s)',mean(results),elapsedTime);
        avg_outer(j) = mean(results);
        fprintf('\n');
    end
    fprintf('average value over %g iterations is %5.2f\n\n\n',outer_iter,mean(avg_outer));
    
    fprintf('\n');
    %%%%%%%%%%% pa-sort-w
    
    for j=1:outer_iter
        fprintf('pa-sorted-w-simple:\t\t ');
        tic;
        v = pa_sorted_simple(I,1);
        fprintf('%g ',results(1)); [Ac,Ar] = MatlabOverpaint(I,v);
        for i=2:iter
           inner_loop;
           v = pa_sorted_simple(A2,1);
           [Ac,Ar] = MatlabOverpaint(A2,v);
        end
        elapsedTime = toc;
        fprintf('\t (avg %5.2f time %g s)',mean(results),elapsedTime);
        avg_outer(j) = mean(results);
        fprintf('\n');
    end
    fprintf('average value over %g iterations is %5.2f\n\n\n',outer_iter,mean(avg_outer));
    
    for j=1:outer_iter
        fprintf('pa-sorted-w-random:\t\t ');
        tic;
        v = pa_sorted_random(I,1);
        fprintf('%g ',results(1)); [Ac,Ar] = MatlabOverpaint(I,v);
        for i=2:iter
           inner_loop;
           v = pa_sorted_random(A2,1);
           [Ac,Ar] = MatlabOverpaint(A2,v);
        end
        elapsedTime = toc;
        fprintf('\t (avg %5.2f time %g s)',mean(results),elapsedTime);
        avg_outer(j) = mean(results);
        fprintf('\n');
    end
    fprintf('average value over %g iterations is %5.2f\n\n\n',outer_iter,mean(avg_outer));
    
    for j=1:outer_iter
        fprintf('pa-sorted-w-mix-alt-row:\t ');
        tic;
        v = pa_sorted_mix(I,1,0,0);
        fprintf('%g ',results(1)); [Ac,Ar] = MatlabOverpaint(I,v);
        for i=2:iter
           inner_loop;
           v = pa_sorted_mix(A2,1,0,0);
           [Ac,Ar] = MatlabOverpaint(A2,v);
        end
        elapsedTime = toc;
        fprintf('\t (avg %5.2f time %g s)',mean(results),elapsedTime);
        avg_outer(j) = mean(results);
        fprintf('\n');
    end
    fprintf('average value over %g iterations is %5.2f\n\n\n',outer_iter,mean(avg_outer));
    
    for j=1:outer_iter
        fprintf('pa-sorted-w-mix-alt-col:\t ');
        tic;
        v = pa_sorted_mix(I,1,0,1);
        fprintf('%g ',results(1)); [Ac,Ar] = MatlabOverpaint(I,v);
        for i=2:iter
           inner_loop;
           v = pa_sorted_mix(A2,1,0,1);
           [Ac,Ar] = MatlabOverpaint(A2,v);
        end
        elapsedTime = toc;
        fprintf('\t (avg %5.2f time %g s)',mean(results),elapsedTime);
        avg_outer(j) = mean(results);
        fprintf('\n');
    end
    fprintf('average value over %g iterations is %5.2f\n\n\n',outer_iter,mean(avg_outer));
    
    for j=1:outer_iter
        fprintf('pa-sorted-w-mix-spr-row:\t ');
        tic;
        v = pa_sorted_mix(I,1,1,0);
        fprintf('%g ',results(1)); [Ac,Ar] = MatlabOverpaint(I,v);
        for i=2:iter
           inner_loop;
           v = pa_sorted_mix(A2,1,1,0);
           [Ac,Ar] = MatlabOverpaint(A2,v);
        end
        elapsedTime = toc;
        fprintf('\t (avg %5.2f time %g s)',mean(results),elapsedTime);
        avg_outer(j) = mean(results);
        fprintf('\n');
    end
    fprintf('average value over %g iterations is %5.2f\n\n\n',outer_iter,mean(avg_outer));
    
    for j=1:outer_iter
        fprintf('pa-sorted-w-mix-spr-col:\t ');
        tic;
        v = pa_sorted_mix(I,1,1,1);
        fprintf('%g ',results(1)); [Ac,Ar] = MatlabOverpaint(I,v);
        for i=2:iter
           inner_loop;
           v = pa_sorted_mix(A2,1,1,1);
           [Ac,Ar] = MatlabOverpaint(A2,v);
        end
        elapsedTime = toc;
        fprintf('\t (avg %5.2f time %g s)',mean(results),elapsedTime);
        avg_outer(j) = mean(results);
        fprintf('\n');
    end
    fprintf('average value over %g iterations is %5.2f\n\n\n',outer_iter,mean(avg_outer));
end
