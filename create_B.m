function B=create_B(Ar,Ac,m,n)
    %diagonal part
    dia = sparse(m+n,m+n);
    Ar2 = Ar';
    Ac2 = Ac';
    for i=1:m
        if((nnz(Ar2(:,i))) && (nnz(Ac2(:,i))))
            dia(n+i,n+i) = 1;
        end
    end
     
    for i=1:n
        if((nnz(Ar(:,i))) && (nnz(Ac(:,i))))
            dia(i,i) = 1;
        end
    end

    %Ac part
    [ic,jc,sc] = find(Ac);
    ic = ic+n;
    Ac = sparse(ic,jc,sc,m+n,m+n);
    
    %Ar part
    Ar = Ar';
    [ir,jr,sr] = find(Ar);
    jr = jr+n;
    Ar = sparse(ir,jr,sr,m+n,m+n);
    
    B = Ac+Ar+dia;
end
    
    