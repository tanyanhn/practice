%your name, your student number, lesson number
clear;
%
%   Euler-Trapezoid Aglorithm with Picard Solver.
%
eps = .0001;
maxm = 10;
u(1) = 973.;
T = 100;
KK = 40
h = T/KK;
t(1)= 0.;
%
%   Begin Time Loop,
%
for k = 1:KK
	oldfeuls =feuls(t(k),u(k));
  	oldu = u(k) + h*oldfeuls;
   t(k+1) = t(k) + h;
%
%   Begin Picard Loop.
%
    	for m=1:maxm
		newu = u(k) + h*.5*(oldfeuls + feuls(t(k+1),oldu));
		if abs(newu-oldu)<eps
			break;
		end
		oldu = newu;
	end
	u(k+1) = newu;
end    	
plot(t,u)
title('your name, your student number, lesson number')
xlabel('time')
ylabel('temperature')

