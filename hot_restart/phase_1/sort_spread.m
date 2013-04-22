function [srt,idx] = sort_spread(in,m,varargin)
if nargin < 3
    ord = 'ascend';
    ord2 = 0;
elseif nargin < 4
    ord2 = 0;
    ord = varargin{1};
else
    ord = varargin{1}; 
    if strcmp(varargin{2},'col');
        ord2 = 1;
    elseif strcmp(varargin{2},'row')
        ord2 = 0;
    else
        error('syntax error: try ''col'' or ''row'' as second parameter');
    end
end
l = length(in);
[srt,idx2] =sort(in,ord);
index = 1;
idx = [];
%idx = zeros(1,l);
while(index <= l)
    index2 = index;
    rows = [];
    cols = [];
    while(index2 <= l && srt(index2) == srt(index))
        if idx2(index2) <=m
            rows = [rows idx2(index2)];
        else
            cols = [cols idx2(index2)];
        end
        index2 = index2+1;
    end
    len = index2 - index;
    if length(cols)<length(rows)
        v1 = mix_spread(cols,rows,1-ord2);
    else
        v1 = mix_spread(cols,rows,ord2);
    end
    idx = [idx v1];
    index = index+len;
end
    
