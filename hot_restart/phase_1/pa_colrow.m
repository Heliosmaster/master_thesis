function [v,l]=pa_colrow(A)
[uncut,cut]=uncut_before_cut(A);
l =length(uncut);
v=[sort(uncut,'descend') sort(cut,'descend')];

