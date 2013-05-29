B = MatlabCreateB(Ac,Ar);
[I2, s, ~, ~, ~, ~, ~, ~, ~, ~, ~] = mondriaan(B,2,0.03,0,0,5);
results(i) = s(4);
fprintf('%5g ',s(4));
Ar2 = I2(1:n,n+1:end)';
Ac2 = I2(n+1:end,1:n);        
A2 = Ar2+Ac2;