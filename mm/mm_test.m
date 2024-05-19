# Script for mm.dat performance metrics
load "mm.dat"
p = [mm(1:5,1)];
Tp = [mm(1:5,2)];
Tp2 = [0; mm(1:4,2)];
_2Tp = [2*Tp];
S = zeros(5, 1);
E = zeros(5, 1);
SC = zeros(5, 1);
for i = 1:length(p)
   S(i) = Tp(1) / Tp(i);
   E(i) = S(i) / p(i) * 100;
   SC(i) = Tp2(i) / _2Tp(i);
endfor
data = [p Tp Tp2 _2Tp S E SC]
save "mm.all.dat" data