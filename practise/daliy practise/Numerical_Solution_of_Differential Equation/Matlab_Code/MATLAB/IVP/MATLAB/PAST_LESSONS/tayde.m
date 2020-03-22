%your name, your student number, lesson number
clear;
y(1) = 70.;
T = 480;
KK = 400
h = T/KK;
t(1)= 0.;
for k = 1:KK
    k1 = ftay(t(k),y(k));
    k2 = ftayt(t(k),y(k)) + ftayu(t(k),y(k))*k1;
    y(k+1) = y(k) + h*(k1 + k2*h/2);
    t(k+1) = t(k) + h;
end
plot(t,y)
title('your name, your student number, lesson number')
xlabel('time')
ylabel('temperature')


