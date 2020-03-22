%your name, your student number, lesson number
clear;
y(1) = 0.;
T = 100.;
KK = 100
h = T/KK;
t(1)= 0.;
for k = 1:KK
   y(k+1) = y(k) + h*fmass(t(k),y(k));
   t(k+1) = t(k) + h;
   y(k+1) = y(k) + .5*h*(fmass(t(k),y(k)) + fmass(t(k+1),y(k+1)));
end
plot(t,y)
title('your name, your student number, lesson number')
xlabel('time')
ylabel('speed')

