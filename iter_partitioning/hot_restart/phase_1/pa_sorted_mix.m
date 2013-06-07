function [v,l] = pa_sorted_mix(A,strategy,varargin)
if nargin < 3
    widow = 1;
    colFirst = 0;
elseif nargin < 4
    widow = varargin{1};
    colFirst = 0;
else
    widow = varargin{1};
    colFirst = varargin{2};
end
[m,~]=size(A);
[uncut,cut]=uncut_before_cut(A);
l = length(uncut);
nz=get_nnz(A);
[valu,iu] = sort_mix(nz(uncut),m,strategy,colFirst);
[~,ic] = sort_mix(nz(cut),m,strategy,colFirst);
if widow
    ru = nnz(valu==1);
    v = [uncut(iu(ru+1:end)) cut(ic) uncut(iu(1:ru))];
else
    v = [uncut(iu) cut(ic)];
end

