% dim=0 row
% dim=1 col
function v=po_alternate(A,varargin)
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
v = mix_alternate(1:m,m+1:n,ord);