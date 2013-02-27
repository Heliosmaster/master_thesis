clear all; close all; clc;

% read the input sparse matrix
matrix = 'impcol_b';
str = ['matrices/' matrix '.mtx'];
A = mmread(str);
%A = sprand(30,30,0.3);
clear str

%iteration number
iter = 2;
i=1;
results = zeros(1,iter);
results0 = zeros(1,iter);

%initial split (8 = twodim)
[I, s, p, q, r, c, rh, ch, B, u, v] = mondriaan(A,2,0.03,0,0,8);
results(1) = s(4);
results0(1) = s(4);
fprintf('%g: comm. vol. = %g\n',1,s(4));

%separating the two parts as S1 and S2
[m,n] = size(A);
[i1,j1,s1] = find(I==1);
Ar0 = sparse(i1,j1,s1,m,n);
[i2,j2,s2] = find(I==2);
Ac0 = sparse(i2,j2,s2,m,n);
[Ac,Ar] = localview(A);

%  figure(ceil(i/2));
%  j = mod(i,2);
%  if (j==0) j=2; end;
%  subplot(2,1,j);
% lab = ['iter: ' int2str(i) '   comm: ' int2str(s(4)) '  Ar/Ac: ' int2str(nnz(Ar)) '/' int2str(nnz(Ac))];
% spy(Ar,'r'); hold on;
% spy(Ac,'g'); hold off;
% xlabel(lab);
 
for i=2:iter
    %pause(1)

%     ic = [1 1 1 2 2];
%     jc = [2 5 6 5 6];
%     sc = [1 1 1 1 1];
% 
%     Ac = sparse(ic,jc,sc,m,n);
%     Ar = I-2*Ac;
    
    % creating the matrix B as in the model
    B = create_B(Ar,Ac,m,n);
   % B0 = create_B(Ar0,Ac0,m,n);
   % B0 = globalview(B0,m,n);
    %figure(i);
    
    % splitting B with the row-net model (onedimcol = 5 in SplitStrategy)
    [I2, s, ~, ~, ~, ~, ~, ~, ~, ~, ~] = mondriaan(B,2,0.03,0,0,5);
    %[I20, s0, ~, ~, ~, ~, ~, ~, ~, ~, ~] = mondriaan(B0,2,0.03,0,0,5);
    results(i) = s(4);
    %results0(i) = s0(4);
    fprintf('%g: comm. vol. = %g\n',i,s(4));
    
    % cleaning the diagonal elements
    for k = 1:m+n
        I2(k,k) = 0;
     %   I20(k,k) = 0;
    end
    
   % figure(i); spy(I2);
    
    % getting back the original Ar and Ac, with new partitioning
    
    Ar2 = I2(1:n,n+1:end)';
    Ac2 = I2(n+1:end,1:n);
    

    
    % reassembling the original matrix, with new partitioning
    A2 = Ar2+Ac2;
    figure(199+i); spy(A2);
%     
%     Ar20 = I20(1:n,n+1:end)';
%     Ac20 = I20(n+1:end,1:n);
%     
%     % reassembling the original matrix, with new partitioning
%     A20 = Ar20+Ac20;
    
        figure(i);
    lab = ['iter: ' int2str(i) '   comm: ' int2str(s(4)) '  Ar/Ac: ' int2str(nnz(Ar2)) '/' int2str(nnz(Ac2))];
    spy(Ar2,'r'); hold on;
    spy(Ac2,'g'); hold off;
    xlabel(lab);
    
    % getting the new Ar and Ac based on new partitioning
    [Ac,Ar] = localview(A2);
%     [i1,j1,s1] = find(A20==1);
%     Ar0 = sparse(i1,j1,s1,m,n);
%     [i2,j2,s2] = find(A20==2);
%     Ac0 = sparse(i2,j2,s2,m,n);

    
    
    %visualizing new partioning
%     
%     if(s(4)==10)
%         figure(9);
%         lab = ['iter: ' int2str(i) '   comm: ' int2str(s(4)) '  Ar/Ac: ' int2str(nnz(Ar)) '/' int2str(nnz(Ac))];
%         spy(Ar,'r'); hold on;
%         spy(Ac,'g'); hold off;
%         xlabel(lab); 
%     end
    
%     figure(ceil(i/2));
%     j = mod(i,2);
%     if (j==0) j=2; end;
%     subplot(2,1,j);
%     subplot(2,1,j);
%     lab = ['iter: ' int2str(i) '   comm: ' int2str(s(4)) '  Ar/Ac: ' int2str(nnz(Ar)) '/' int2str(nnz(Ac))];
%     spy(Ar,'r'); hold on;
%     spy(Ac,'g'); hold off;
%     xlabel(lab); 
     
    
end

[best,k] = min(results);
fprintf('best=%g at iteration %g\n',best,k);
figure(101)
plot(results); 
%hold on; plot(results0,'g');
