function [v,l]=pa_mix(A,strategy,varargin)
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
cut_rows = cut(cut<=m);
cut_cols = cut(cut>m);
if ~strategy
    v1 = mix_alternate(uncut_rows,uncut_cols,ord);
    v2 = mix_alternate(cut_rows,cut_cols,ord);
else
    v1 = mix_spread(uncut_rows,uncut_cols,ord);
    v2 = mix_spread(cut_rows,cut_cols,ord);
end

v=[v1 v2];
end
