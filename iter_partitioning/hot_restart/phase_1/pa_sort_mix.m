function [v,l] = pa_sort_mix(A,strategy,varargin)
if nargin < 3
    widow = 1;
    ord = 'ascend';
    ord2 = 0;
elseif nargin < 4
    widow = varargin{1};
    ord = 'ascend';
    ord2 = 0;
elseif nargin < 5
    widow = varargin{1};
    ord = varargin{2};
    ord2 = 0;
else
    widow = varargin{1};
    ord = varargin{2};
    ord2 = varargin{3};
end
[m,~]=size(A);
[uncut,cut]=uncut_before_cut(A);
l = length(uncut);
nz=get_nnz(A);
[valu,iu] = sort_mix(nz(uncut),m,strategy,ord,ord2);
[~,ic] = sort_mix(nz(cut),m,strategy,ord,ord2);
if widow
    ru = nnz(valu==1);
    v = [uncut(iu(ru+1:end)) cut(ic) uncut(iu(1:ru))];
else
    v = [uncut(iu) cut(ic)];
end

