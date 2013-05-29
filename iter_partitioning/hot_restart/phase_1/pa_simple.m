function [v,l]=pa_simple(A,varargin)
if nargin < 2
    ord = 'row';
else
    ord = varargin{1};
end
[uncut,cut]=uncut_before_cut(A);
l =length(uncut);
if strcmp(ord,'row');
    v=[sort(uncut,'ascend') sort(cut,'ascend')];
else
    v=[sort(uncut,'descend') sort(cut,'descend')];
end