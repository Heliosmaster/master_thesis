% v=mix_spread(r,c,ord)
%
% given the two vectors r and c, combines them in an spread fashion.
% Example:     r c c r c c r c c
%               
% the first element of v belongs to the shortest between r and c
% if ord=0, to the longest otherwise.
%
% the elements of both r and c are randomly permuted before constructing
% the final vector. 

function v=mix_spread(r,c,ord)
lr = length(r);
lc = length(c);

% scrambling of r and c for added entropy
r = r(randperm(lr));
c = c(randperm(lc));

% detecting which one is shortest and longest between r and c
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

% performing the division with remainder, such that ll = q*ls+s
q = floor(ll/ls);
s = mod(ll,ls);

% intialization of the output vector, without remainder
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

% adding the remainder
v = [v long(ll-s+1:end)];
