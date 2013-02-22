clear all; close all; clc;

% read the input sparse matrix
matrix = 'impcol_b';
str = ['matrices/' matrix '.mtx'];
A = mmread(str);
%A = sprand(30,30,0.3);
clear str

%iteration number
iter = 100;
i=1;
results = zeros(1,iter);

%initial split (8 = twodim)
[I, s, p, q, r, c, rh, ch, B, u, v] = mondriaan(A,2,0.03,0,0,8);
results(1) = s(4);
fprintf('%g: comm. vol. = %g\n',1,s(4));

%separating the two parts as S1 and S2
[m,n] = size(A);
[i1,j1,s1] = find(I==1);
Ar = sparse(i1,j1,s1,m,n);
[i2,j2,s2] = find(I==2);
Ac = sparse(i2,j2,s2,m,n);

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
    B1 = create_B(Ar,Ac,m,n);
    B2 = create_B(Ac,Ar,m,n);
    %figure(i);
    
    % splitting B with the row-net model (onedimcol = 5 in SplitStrategy)
    [I1, s1, p, q, r, c, rh, ch, ~, u, v] = mondriaan(B1,2,0.03,0,0,5);
    [I2, s2, p, q, r, c, rh, ch, ~, u, v] = mondriaan(B2,2,0.03,0,0,5);
    if s1(4) < s2(4)
        I = I1;
        s = s1;
    else
        I=I2;
        s=s2;
    end
    results(i) = s(4);
    fprintf('%g: vol = %g\n',i,s(4));
    
    % cleaning the diagonal elements
    for k = 1:m+n
        I(k,k) = 0;
    end
    
    % getting back the original Ar and Ac, with new partitioning
    
    Ar2 = I(1:n,n+1:end)';
    Ac2 = I(n+1:end,1:n);
    
    % reassembling the original matrix, with new partitioning
    A2 = Ar2+Ac2;
    
    % getting the new Ar and Ac based on new partitioning
    [i1,j1,s1] = find(A2==1);
    Ar = sparse(i1,j1,s1,m,n);
    [i2,j2,s2] = find(A2==2);
    Ac = sparse(i2,j2,s2,m,n);
    
    %visualizing new partioning
    
    if(s(4)==10)
        figure(9);
        lab = ['iter: ' int2str(i) '   comm: ' int2str(s(4)) '  Ar/Ac: ' int2str(nnz(Ar)) '/' int2str(nnz(Ac))];
        spy(Ar,'r'); hold on;
        spy(Ac,'g'); hold off;
        xlabel(lab); 
    end
    
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
fprintf('best: %g at iter %g\n',best,k);
