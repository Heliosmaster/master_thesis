function [v,l] = pa_sorted_random(A,varargin)
if nargin < 2
    widow = 1;
else
    widow = varargin{1};
end
[m,~]=size(A);
[uncut,cut]=uncut_before_cut(A);
l = length(uncut);
nz=get_nnz(A);
[valu,iu] = sort_random(nz(uncut),m,'ascend');
[~,ic] = sort_random(nz(cut),m,'ascend');
if widow
    ru = nnz(valu==1);
    v = [uncut(iu(ru+1:end)) cut(ic) uncut(iu(1:ru))];
else
    v = [uncut(iu) cut(ic)];
end