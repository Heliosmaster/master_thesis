%close all; clc; clear all;
matrix = 'dfl001';
str = ['../../matrices/' matrix '.mtx'];
A = mmread(str);

clear str

%iteration number
outeriter = 10;
iter = 10;
flag = 1; % 0 = partition oblivious, 1 = partition aware
i=1;
results = zeros(1,iter);
values = zeros(outeriter,iter);
fprintf('\n%s\n\n',matrix);

counter = 0;

tStart = tic;

%initial split (8 = twodim)
for j=1:outeriter
[I, s, ~, ~ , ~, ~, ~, ~, ~, ~, ~] = mondriaan(A,2,0.03,2,0,8);
results(1) = s(4);
[m,n] = size(A);

fprintf('localview:\t ');
values(j,1) = s(4);


fprintf('%4g | ',results(1));

[Ac,Ar] = MatlabLocalview(I,flag);
for i=2:iter+1
    inner_loop;
    values(j,i) = s(4);
    [Ac,Ar] = MatlabLocalview(A2,flag);
end
fprintf('\n');
end
fprintf('--------------------\n');
fprintf('\t\t');
fprintf('%5.0f | ',mean(values(:,1)));
for i=2:iter+1
    fprintf('%5.0f ',mean(values(:,i)));
end
fprintf('\n');
% fprintf('\t time %g s',elapsedTime); % (avg %5.2f
% fprintf('\n');

