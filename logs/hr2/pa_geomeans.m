%A = dlmread('table.txt');
means_vec = [geomean(A(:,1:8)) geomean(A([1:12 14:18],9:12))];
norm_vec = zeros(size(means_vec));

for i=1:6
	norm_vec(2*i-1) = 1.0;
	norm_vec(2*i) = means_vec(2*i)/means_vec(2*i-1);
end

	
