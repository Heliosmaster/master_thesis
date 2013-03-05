function q = reverse_perm(p)
    q = zeros(size(p));
    for k=1:length(p)
        q(p(k)) = k;
    end
end