function showIteration(A,s,i,j)
    [m,n] = size(A);
    [i1,j1,s1] = find(A==1);
    An1 = sparse(i1,j1,s1,m,n);
    [i2,j2,s2] = find(A==2);
    An2 = sparse(i2,j2,s2,m,n);

    figure(i);
    lab = ['iter: ' int2str(i) '   comm: ' int2str(s(4)) '  red/green: ' int2str(nnz(An1)) '/' int2str(nnz(An2))];
    spy(An1,'r'); hold on;
    spy(An2,'g'); hold off;
    xlabel(lab);
    pause(j);
end