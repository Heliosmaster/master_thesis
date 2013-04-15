%clear all; close all; clc;

printIteration = 0;
% read the input sparse matrix
matrix = 'dfl001';
str = ['matrices/' matrix '.mtx'];
A = mmread(str);
%A = sprand(30,30,0.3);
clear str

%iteration number
iter = 100;
i=1;
results = zeros(1,iter);

%initial split (8 = twodim)
[I, s, ~, ~ , ~, ~, ~, ~, ~, ~, ~] = mondriaan(A,2,0.03,2,0,8);
results(1) = s(4);
fprintf('%g: comm. vol. = %g\n',1,s(4));

%separating the two parts as S1 and S2
[m,n] = size(A);

% if printIteration
%     showIteration(I,s,1,1);
% end

% counterglobalview = 0;

[Ac,Ar] = localview(A);
% [p,q,r,c] = super_sbd(I);
% [Ar,Ac]=super_sbdview(I,p,q,r,c);

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
   
    % creating the matrix B as in the model
    %B = create_B(Ar,Ac,m,n);
    B = MatlabCreateB(Ac,Ar);
%     if i ~= 2 && (results(i-1) == results(i-2)) && counterglobalview < 3;
%         B = globalview(B,m,n);
%         counterglobalview = counterglobalview+1;
%     end
   
    
    % splitting B with the row-net model (onedimcol = 5 in SplitStrategy)
    [I2, s, ~, ~, ~, ~, ~, ~, ~, ~, ~] = mondriaan(B,2,0.03,0,0,5);
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
        

%     if printIteration || s(4) == 10
%       showIteration(A2,s,1,0.5)
%     end
    

%     [p,q,r,c] = super_sbd(A2);
%     [Ar,Ac]=super_sbdview(A2,p,q,r,c);
%     % getting the new Ar and Ac based on new partitioning
 [Ac,Ar] = localview(A2);
  
    
end

[best,k] = min(results);
fprintf('best=%g at iteration %g \t avg: %g\n',best,k,mean(results));
figure(101)
plot(results); 
