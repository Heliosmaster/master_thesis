function [v,l]=pa_spread(A,varargin)
[uncut,cut]=uncut_before_cut(A);
l =length(uncut);
[m,~] = size(A);

if nargin < 2
    ord = 0;
else
    ord = varargin{1};
end

uncut_rows = uncut(uncut<=m);
uncut_cols = uncut(uncut>m);
v1 = mix_spread(uncut_rows,uncut_cols,ord);

cut_rows = cut(cut<=m);
cut_cols = cut(cut>m);
v2 = mix_spread(cut_rows,cut_cols,ord);

v=[v1 v2];
end
