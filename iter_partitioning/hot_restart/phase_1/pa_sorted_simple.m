function [v,l]=pa_sorted_simple(A,varargin)
if nargin < 2
    widow = 1;
else
    widow = varargin{1};
end
[uncut,cut]=uncut_before_cut(A);
l = length(uncut);
nz=get_nnz(A);
[valu,iu] = sort(nz(uncut),'ascend');
[valc,ic] = sort(nz(cut),'ascend');
if widow
    ru = nnz(valu==1);
		rc = nnz(valc==1);
		v = [uncut(iu(ru+1:end)) cut(ic(rc+1:end)) uncut(iu(1:ru)) cut(ic(1:rc))];
else
    v = [uncut(iu) cut(ic)];
end
