function [srt,idx] = sort_mix(in,m,strategy,ord,ord2)
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
    if isempty(rows)
        v1 = cols;
    elseif isempty(cols)
        v1 = rows;
    else
        if ~strategy
            v1 = mix_alternate(rows,cols,ord);
        else
            if length(cols)<length(rows)
                v1 = mix_spread(cols,rows,1-ord2);
            else
                v1 = mix_spread(cols,rows,ord2);
            end
        end
    end
    
    idx = [idx v1];
    index = index+len;
end
    
