% [P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13] = supersplit_subparts(I,p,q,r,c)
% 
% splits a matrix into its SSBD components
% --------------------
% | 1 | 2 | ~ | ~ | ~ |
% | 3 | 4 | 5 | ~ | ~ |
% | ~ | 6 | 7 | 8 | ~ |
% | ~ | ~ | 9 | 10| 11|
% | ~ | ~ | ~ | 12| 13|
% --------------------
% 
% TODO: explicit explanation of the 13 parts


function [P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13] = supersplit_subparts(I,p,q,r,c)
    P = (I(p,q));
    size(P)
    P1 = P(1:r(2)-1,1:c(2)-1);
    P2 = P(1:r(2)-1,c(2):c(3)-1);
    P3 = P(r(2):r(3)-1,1:c(2)-1);
    P4 = P(r(2):r(3)-1,c(2):c(3)-1);
    P5 = P(r(2):r(3)-1,c(3):c(4)-1);
    P6 = P(r(3):r(4)-1,c(2):c(3)-1);
    P7 = P(r(3):r(4)-1,c(3):c(4)-1);
    P8 = P(r(3):r(4)-1,c(4):c(5)-1);
    P9 = P(r(4):r(5)-1,c(3):c(4)-1);
    P10 = P(r(4):r(5)-1,c(4):c(5)-1);
    P11 = P(r(4):r(5)-1,c(5):c(6)-1);
    P12 = P(r(5):r(6)-1,c(4):c(5)-1);
    P13 = P(r(5):r(6)-1,c(5):c(6)-1);
end