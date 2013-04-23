function [v,l] = pa_fullsort_mix(A,strategy,varargin)
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
[~,iu] = sort_mix(nz(uncut),m,strategy,ord,ord2);
[~,ic] = sort_mix(nz(cut),m,strategy,ord,ord2);
v = [uncut(iu) cut(ic)];