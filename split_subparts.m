% [P1,P2,P3,P4,P5,P6,P7] = split_subparts(I,p,q,r,c)
% 
% splits a matrix into its SBD components
% -------------
% | 1 | 2 | ~ |
% | 3 | 4 | 5 |
% | ~ | 6 | 7 |
% -------------
% 
% part 1, uncut row+col (red)
% part 2, uncut row (red), cut col
% part 3 uncut col (red), cut row
% part 4 cut row, cut col
% part 5 uncut col (green), cut row
% part 6, uncut row (green), cut col
% part 7, uncut row+col (green)
function [P1,P2,P3,P4,P5,P6,P7] = split_subparts(I,p,q,r,c)
    P = (I(p,q));
    P1 = P(1:r(2)-1,1:c(2)-1);
    P2 = P(1:r(2)-1,c(2):c(3)-1);
    P3 = P(r(2):r(3)-1,1:c(2)-1);
    P4 = P(r(2):r(3)-1,c(2):c(3)-1);
    P5 = P(r(2):r(3)-1,c(3):c(4)-1);
    P6 = P(r(3):r(4)-1,c(2):c(3)-1);
    P7 = P(r(3):r(4)-1,c(3):c(4)-1);
end