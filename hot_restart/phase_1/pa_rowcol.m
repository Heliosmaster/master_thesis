function [v,l]=pa_rowcol(A)
[uncut,cut]=uncut_before_cut(A);
l =length(uncut);
v=[sort(uncut) sort(cut)];

