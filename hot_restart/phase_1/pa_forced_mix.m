function [v,l]=pa_forced_mix(A,varargin)
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
lr = length(uncut_rows);
lc = length(uncut_cols);
uncut_rows = uncut_rows(randperm(lr));
uncut_cols = uncut_cols(randperm(lc));
v1 = zeros(1,2*max(lr,lc));
if ~ord
    v1(1:2:2*lr) = uncut_rows;
    v1(2:2:2*lc) = uncut_cols;
else
    v1(2:2:2*lr) = uncut_rows;
    v1(1:2:2*lc) = uncut_cols;
end
v1 = nonzeros(v1)';

cut_rows = cut(cut<=m);
cut_cols = cut(cut>m);
lr = length(cut_rows);
lc = length(cut_cols);
cut_rows = cut_rows(randperm(lr));
cut_cols = cut_cols(randperm(lc));
v2 = zeros(1,2*max(lr,lc));
v2(1:2:2*lr) = cut_rows;
v2(2:2:2*lc) = cut_cols;
v2 = nonzeros(v2)';

v=[v1 v2];
end
