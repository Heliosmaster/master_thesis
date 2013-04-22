function [v,l] = pa_fullsort_alternate(A,varargin)
if nargin < 2
    ord = 'ascend';
    ord2 = 'row';
elseif nargin < 3
    ord = varargin{1};
    ord2 = 'row';
else
    ord = varargin{1};
    ord2 = varargin{2};
end
[m,~]=size(A);
[uncut,cut]=uncut_before_cut(A);
l = length(uncut);
nz=get_nnz(A);
[~,iu] = sort_alternate(nz(uncut),m,ord,ord2);
[~,ic] = sort_alternate(nz(cut),m,ord,ord2);
v = [uncut(iu) cut(ic)];