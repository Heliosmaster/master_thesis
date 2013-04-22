function v=mix_alternate(r,c,ord)
lr = length(r);
lc = length(c);
r = r(randperm(lr));
c = c(randperm(lc));
v = zeros(1,2*max(lr,lc));
if ~ord
    v(1:2:2*lr) = r;
    v(2:2:2*lc) = c;
else
    v(2:2:2*lr) = r;
    v(1:2:2*lc) = c;
end
v = nonzeros(v)';