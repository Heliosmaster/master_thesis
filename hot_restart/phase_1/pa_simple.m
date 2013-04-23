function [v,l]=pa_simple(A,ord)
[uncut,cut]=uncut_before_cut(A);
l =length(uncut);
if ~ord
    v=[sort(uncut) sort(cut)];
else
    v=[sort(uncut,'descend') sort(cut,'descend')];
end
    

