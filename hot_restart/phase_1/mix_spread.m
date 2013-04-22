function v=mix_spread(r,c,ord)
lr = length(r);
lc = length(c); 
if lr < lc
    short = r;
    long = c;
    ls =lr;
    ll = lc;
else
    short = c;
    long = r;
    ls =lc;
    ll = lr;
end

q = floor(ll/ls);
s = mod(ll,ls);
v = zeros(1,ll+ls-s);

if ~ord
    % short first
    v(1:q+1:ll+ls-s) = short;
    for i=2:q+1
        v(i:q+1:ll+ls-s) = long(i-1:q:ll-s);
    end
else
    % long first
    for i=1:q
        v(i:q+1:ll+ls-s) = long(i:q:ll-s);
    end
    v(q+1:q+1:ll+ls-s) = short;
end
    
v = [v long(ll-s+1:end)];
