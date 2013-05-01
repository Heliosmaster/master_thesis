function [v,l]=pa_sort_simple(A,varargin)
if nargin < 2
    widow = 1;
    ord = 'ascend';
elseif nargin < 3
    widow = varargin{1};
else
    widow = varargin{1};
    ord = varargin{2};
end
[uncut,cut]=uncut_before_cut(A);
l = length(uncut);
nz=get_nnz(A);
[valu,iu] = sort(nz(uncut),ord);
[~,ic] = sort(nz(cut),ord);
if widow
    ru = nnz(valu==1);
    v = [uncut(iu(ru+1:end)) cut(ic) uncut(iu(1:ru))];
else
    v = [uncut(iu) cut(ic)];
end