function [Ar,Ac]=sbdview(I,p,q,r,c)
    [m,n] = size(I);
    mi = [r(2)-r(1),r(3)-r(2),r(4)-r(3)];
    ni = [c(2)-c(1),c(3)-c(2),c(4)-c(3)];
    ir = [];
    jr = [];
    ic = [];
    jc = [];
    [P1,P2,P3,P4,P5,P6,P7] = split_subparts(I,p,q,r,c);
    
    % converting to vectors
    [i1,j1,~] = find(P1);
    [i2,j2,~] = find(P2);
    [i3,j3,~] = find(P3);
    %[i4,j4,~] = find(P4);
    [i5,j5,~] = find(P5);
    [i6,j6,~] = find(P6);
    [i7,j7,~] = find(P7);
    
    % shifting
    j2 = j2 + ni(1);
    
    i3 = i3 + mi(1);
    
    %i4 = i4 + mi(1);
    %j4 = j4 + ni(1);
    
    i5 = i5 + mi(1);
    j5 = j5 + c(3)-1;
    
    i6 = i6 + r(3)-1;
    j6 = j6 + ni(1);
    
    i7 = i7 + r(3)-1;
    j7 = j7 + c(3)-1;

    % P1
    if mi(1) > ni(1)
        %rows are on avg shorter, assign to Ar
        ir = [ir i1];
        jr = [jr j1];
    else
        %assign to Ac
        ic = [ic i1];
        jc = [jc j1];
    end
    
    %P2
    if mi(1) > ni(2)
       %rows are on avg shorter, assign to Ar
        ir = [ir; i2];
        jr = [jr; j2];
    else
        %assign to Ac
        ic = [ic; i2];
        jc = [jc; j2];
    end
    
    %P3
    if mi(2) > ni(1)
       %rows are on avg shorter, assign to Ar
        ir = [ir; i3];
        jr = [jr; j3];
    else
        %assign to Ac
        ic = [ic; i3];
        jc = [jc; j3];
    end
    
    %P4
    [Ac4,Ar4] = localview(P4);
    [ir4,jr4,~] = find(Ar4);
    [ic4,jc4,~] = find(Ac4);
    
    ir4 = ir4 + mi(1);
    ic4 = ic4 + mi(1);
    jr4 = jr4 + ni(1);
    jc4 = jc4 + ni(1);
    
    ir = [ir; ir4];
    jr = [jr; jr4];
    ic = [ic; ic4];
    jc = [jc; jc4];
    
    %P5
    if mi(2) > ni(3)
       %rows are on avg shorter, assign to Ar
        ir = [ir; i5];
        jr = [jr; j5];
    else
        %assign to Ac
        ic = [ic; i5];
        jc = [jc; j5];
    end
    
    %P6
    
    if mi(3) > ni(2)
       %rows are on avg shorter, assign to Ar
        ir = [ir; i6];
        jr = [jr; j6];
    else
        %assign to Ac
        ic = [ic; i6];
        jc = [jc; j6];
    end
    
    %P7
    if mi(1) > ni(1)
        %rows are on avg shorter, assign to Ar
        ir = [ir; i7];
        jr = [jr; j7];
    else
        %assign to Ac
        ic = [ic; i7];
        jc = [jc; j7];
    end
   p1 = reverse_perm(p);
   q1 = reverse_perm(q);
   Ar = sparse(ir,jr,ones(size(ir)),m,n);
   Ar = Ar(p1,q1);
   Ac = sparse(ic,jc,ones(size(ic)),m,n);
   Ac = Ac(p1,q1);
end