%Jane Doe, 348384310, lesson 2 (SAMPLE)
clear;
y(1) = 100.;
T = 100;
KK = 50
h = T/KK;
t(1)= 0.;
for k = 1:KK
    y(k+1) = y(k) + h*feul(t(k),y(k));
    t(k+1) = t(k) + h;
end
plot(t,y)
title('Zhilin Li, 348384310, lesson 2 (SAMPLE)')
xlabel('time')
ylabel('temperature')

