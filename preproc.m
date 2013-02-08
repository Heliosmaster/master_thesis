clear all; close all; clc;

% read the input sparse matrix
matrix = 'impcol_b';
str = ['matrices/' matrix '.mtx'];
A = mmread(str);
%A = sprand(30,30,0.3);
clear str

%iteration number
iter = 10;

results = zeros(1,iter);

%initial split
[I, s, p, q, r, c, rh, ch, B, u, v] = mondriaan(A,2,0.03,0,0,8);
results(1) = s(4);
fprintf('%g: comm. vol. = %g\n',1,s(4));

%separating the two parts as S1 and S2
[m,n] = size(A);
[i1,j1,s1] = find(I==1);
Ar = sparse(i1,j1,s1,m,n);
[i2,j2,s2] = find(I==2);
Ac = sparse(i2,j2,s2,m,n);

 figure(1);
 spy(Ar,'r'); hold on;
 spy(Ac,'g'); hold off;
% 

for i=2:iter
    pause(1)

%     ic = [1 1 1 2 2];
%     jc = [2 5 6 5 6];
%     sc = [1 1 1 1 1];
% 
%     Ac = sparse(ic,jc,sc,m,n);
%     Ar = I-2*Ac;
    
    % creating the matrix B as in the model
    B = create_B(Ar,Ac,m,n);
    %figure(i);
    
    % splitting B with the row-net model (onedimcol = 5 in SplitStrategy)
    [I2, s, p, q, r, c, rh, ch, B, u, v] = mondriaan(B,2,0.03,0,0,5);
    results(i) = s(4);
    fprintf('%g: comm. vol. = %g\n',i,s(4));
    
    % cleaning the diagonal elements
    for k = 1:m+n
        I2(k,k) = 0;
    end
    
    % getting back the original Ar and Ac, with new partitioning
    
    Ar2 = I2(1:n,n+1:end)';
    Ac2 = I2(n+1:end,1:n);
    
    % reassembling the original matrix, with new partitioning
    A2 = Ar2+Ac2;
    
    % getting the new Ar and Ac based on new partitioning
    [i1,j1,s1] = find(A2==1);
    Ar = sparse(i1,j1,s1,m,n);
    [i2,j2,s2] = find(A2==2);
    Ac = sparse(i2,j2,s2,m,n);
    
    %visualizing new partioning
    
     figure(i);
     spy(Ar,'r'); hold on;
     spy(Ac,'g'); hold off;
     
     
    
end

[best,k] = min(results);
fprintf('best=%g at iteration %g\n',best,k);
