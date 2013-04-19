function [srt,idx] = sort_mix(in,m,varargin)
if nargin < 3
    ord = 'ascend';
    ord2 = 0;
elseif nargin < 4
    ord2 = 0;
else
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
    lr = length(rows);
    rows = rows(randperm(lr));
    lc = length(cols);
    cols = cols(randperm(lc));
    v1 = zeros(1,2*max(lr,lc));
    if ~ord2
        v1(1:2:2*lr) = rows;
        v1(2:2:2*lc) = cols;
    else
        v1(1:2:2*lc) = cols;
        v1(2:2:2*lr) = rows;
    end
    v1 = nonzeros(v1)';
    idx = [idx v1];
    index = index+len;
end
    
