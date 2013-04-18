% dim=0 row
% dim=1 col
function v=po_forced_mix(A,varargin)
[m,n]=size(A);
if nargin>1
    if strcmp(varargin{1},'col');
        ord = 1;
    elseif strcmp(varargin{1},'row')
        ord = 0;
    else
        error('syntax error: try ''col'' or ''row'' as second parameter');
    end
else
    ord =0;
end

if ord
    perm1 = randperm(m);
    perm2 = m+randperm(n);
    
else
    perm1 = m+randperm(n);
    perm2 = randperm(m);
    
end
l1 = length(perm1);
l2 = length(perm2);

v = zeros(1,2*max(l1,l2));
v(1:2:2*l1) = perm1;
v(2:2:2*l2) = perm2;

v = nonzeros(v)';