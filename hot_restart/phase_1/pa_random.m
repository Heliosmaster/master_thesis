function [v,l]=pa_random(A)
[uncut,cut]=uncut_before_cut(A);
l =length(uncut);
perm1 = randperm(l);
perm2 =randperm(length(cut));
v=[uncut(perm1) cut(perm2)];


