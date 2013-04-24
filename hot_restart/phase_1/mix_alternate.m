% v=mix_alternate(r,c,ord)
%
% given the two vectors r and c, combines them in an alternate fashion.
% Examples:     r c r c r c r
%               c r c c c c c
%
% the first element of v belongs to r if ord=0, c otherwise.
%
% the elements of both r and c are randomly permuted before constructing
% the final vector. 

function v=mix_alternate(r,c,ord)
lr = length(r);
lc = length(c);

% scrambling of r and c for added entropy
r = r(randperm(lr));
c = c(randperm(lc));

% initialization of the output vector with dummy nonzeros
v = zeros(1,2*max(lr,lc));

% actual filling
if ~ord
    % r goes in odd positions
    v(1:2:2*lr) = r;
    % c goes to even positions
    v(2:2:2*lc) = c;
else
    % r goes in even positions
    v(2:2:2*lr) = r;
    % c goes in odd positions
    v(1:2:2*lc) = c;
end

% removal of the extra nonzeros
v = nonzeros(v)';