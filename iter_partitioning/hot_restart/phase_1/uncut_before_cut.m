function [uncut,cut]=uncut_before_cut(A)
split = get_split(A);
[~,v]=sort(split,'descend');
len=nnz(split);
cut = v(1:len);
uncut = v(len+1:end);

