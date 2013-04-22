function [v,l]=pa_alternate(A,varargin)
[uncut,cut]=uncut_before_cut(A);
l =length(uncut);
[m,~] = size(A);

if nargin>1
    if strcmp(varargin{1},'col');
        ord = 1;
    elseif strcmp(varargin{1},'row')
        ord = 0;
    else
        error('syntax error: try ''col'' or ''row'' as second parameter');
    end
else
    ord =0;
end

uncut_rows = uncut(uncut<=m);
uncut_cols = uncut(uncut>m);
v1 = mix_alternate(uncut_rows,uncut_cols,ord);

cut_rows = cut(cut<=m);
cut_cols = cut(cut>m);
v2 = mix_alternate(cut_rows,cut_cols,ord);

v=[v1 v2];
end
