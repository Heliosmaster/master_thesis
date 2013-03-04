clear all; close all; clc;

% read the input sparse matrix
% matrix = 'impcol_b';
matrix = 'cage6';
str = ['matrices/' matrix '.mtx'];
A = mmread(str);
%A = sprand(30,30,0.3);
clear str

%iteration number
%initial split (8 = twodim)
[I, s, p, q, r, c, rh, ch, B, u, v] = mondriaan(A,2,0.03,2,0,8);
mi = [r(2)-r(1),r(3)-r(2),r(4)-r(3)];
ni = [c(2)-c(1),c(3)-c(2),c(4)-c(3)];

P = (I(p,q));
%part 1, uncut red  (1) row+col
P1 = P(1:r(2)-1,1:c(2)-1);
if mi(1) > ni(1)
    %rows are on avg shorter, assign to Ar
else
    %assign to Ac
end

%part 2, uncut row (red), cut col
P2 = P(1:r(2)-1,c(2):c(3)-1);
    % assign empty rows to Ac else to Ar

%part 3 uncut col (red), cut row
P3 = P(r(2):r(3)-1,1:c(2)-1);

%part 4 cut row, cut col
P4 = P(r(2):r(3)-1,c(2):c(3)-1);

%part 5 uncut col (green), cut row
P5 = P(r(2):r(3)-1,c(3):c(4)-1);

%part 6, uncut row (green), cut col
P6 = P(r(3):r(4)-1,c(2):c(3)-1);

%part 7, uncut row+col (green)
P7 = P(r(3):r(4)-1,c(3):c(4)-1);
