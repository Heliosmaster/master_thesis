function [v,l]=pa_unsorted_mix(A,strategy,varargin)
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

if isempty(uncut_rows)
    v1 = uncut_cols;
elseif isempty(uncut_cols)
    v1 = uncut_rows;
else
    if ~strategy
        v1 = mix_alternate(uncut_rows,uncut_cols,ord);
    else
        v1 = mix_spread(uncut_rows,uncut_cols,ord);    
    end
end

if isempty(cut_rows)
    v2 = cut_cols;
elseif isempty(cut_cols)
    v2 = cut_rows;
else
    if ~strategy
        v2 = mix_alternate(cut_rows,cut_cols,ord);
    else
        v2 = mix_spread(cut_rows,cut_cols,ord);    
    end
end

v=[v1 v2];
end
