% pos: 0 start, 1 middle, 2 end
function v=scramble_at(v,pos,alpha)
len = floor(alpha*length(v));
if pos==0
    q = v(1:len);
    v(1:len) = q(randperm(len));
elseif pos==1
    st = floor(length(v)-len)/2;
    en = st+len;
    q = v(st:en);
    v(1:len) = q(randperm(len));
else
    q = v(len:end);
    v(len:end) = q(randperm(len));
end


