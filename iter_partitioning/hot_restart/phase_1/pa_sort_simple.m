function [v,l]=pa_sort_simple(A,varargin)
if nargin < 2
    widow = 1;
else
    widow = varargin{1};
end
[uncut,cut]=uncut_before_cut(A);
l = length(uncut);
nz=get_nnz(A);
[valu,iu] = sort(nz(uncut),'ascend');
[~,ic] = sort(nz(cut),'ascend');
if widow
    ru = nnz(valu==1);
    v = [uncut(iu(ru+1:end)) cut(ic) uncut(iu(1:ru))];
else
    v = [uncut(iu) cut(ic)];
end