function [srt,idx] = sort_random(in,varargin)
if nargin < 2
    ord = 'ascend';
end
l = length(in);
[srt,idx2] =sort(in,ord);
index = 1;
idx = [];
%idx = zeros(1,l);
while(index <= l)
    index2 = index;
    while(index2 <= l && srt(index2) == srt(index))
        index2 = index2+1;
    end
    len = index2 - index;
    perm = randperm(len);
    idx = [idx idx2(index+perm-1)];
    index = index+len;
end
    
