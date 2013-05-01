function [v,l]=pa_simple(A,varargin)
if nargin < 2
    ord = 'ascend';
else
    ord = varargin{1};
end
[uncut,cut]=uncut_before_cut(A);
l =length(uncut);
v=[sort(uncut,ord) sort(cut,ord)];

    

