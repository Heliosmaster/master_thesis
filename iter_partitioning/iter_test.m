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
    iter = 10;
    i=1;
    results = zeros(1,iter);

    fprintf('\n%s\n\n',matrix);

    %initial split (8 = twodim)
%     [I, s, ~, ~ , ~, ~, ~, ~, ~, ~, ~] = mondriaan(A,2,0.03,2,0,4);
%     disp(s(4));
%     [I, s, ~, ~ , ~, ~, ~, ~, ~, ~, ~] = mondriaan(A,2,0.03,2,0,5);
%     disp(s(4));
    [I, s, ~, ~ , ~, ~, ~, ~, ~, ~, ~] = mondriaan(A,2,0.03,2,0,8);
    results(1) = s(4);
    %separating the two parts as S1 and S2
    [m,n] = size(A);

    %%%%%%%%%%% po-unsorted

    fprintf('po-unsorted-simple-row:\t\t ');
    tic;
    v = po_simple(I,'row');
    fprintf('%g ',results(1)); [Ac,Ar] = MatlabOverpaint(I,v);
    for i=2:iter
        B = MatlabCreateB(Ac,Ar);
        [I2, s, ~, ~, ~, ~, ~, ~, ~, ~, ~] = mondriaan(B,2,0.03,0,0,5);
        results(i) = s(4);
        fprintf('%5g ',s(4));
        Ar2 = I2(1:n,n+1:end)';
        Ac2 = I2(n+1:end,1:n);        
        A2 = Ar2+Ac2;
        v = po_simple(A2,'row');
        [Ac,Ar] = MatlabOverpaint(A2,v);
    end
    elapsedTime = toc;
    fprintf('\t (avg %5.2f time %g s)',mean(results),elapsedTime);
    fprintf('\n');
    
    
    fprintf('po-unsorted-simple-col:\t\t ');
    tic;
    v = po_simple(I,'col');
    fprintf('%g ',results(1)); [Ac,Ar] = MatlabOverpaint(I,v);
    for i=2:iter
        B = MatlabCreateB(Ac,Ar);
        [I2, s, ~, ~, ~, ~, ~, ~, ~, ~, ~] = mondriaan(B,2,0.03,0,0,5);
        results(i) = s(4);
        fprintf('%5g ',s(4));
        Ar2 = I2(1:n,n+1:end)';
        Ac2 = I2(n+1:end,1:n);        
        A2 = Ar2+Ac2;
        v = po_simple(A2,'col');
        [Ac,Ar] = MatlabOverpaint(A2,v);
    end
    elapsedTime = toc;
    fprintf('\t (avg %5.2f time %g s)',mean(results),elapsedTime);
    fprintf('\n');
   
end
