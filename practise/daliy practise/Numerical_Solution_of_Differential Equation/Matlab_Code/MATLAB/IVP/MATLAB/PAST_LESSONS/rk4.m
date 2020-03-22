%your name, your student number, lesson number
%clear;
T = 10;
x(1) = 110;
KK = 50
h = T/KK;
t(1)= 0.;
for k = 1:KK
    k1 = h*fpop(t(k),x(k));
    k2 = h*fpop(t(k)+.5*h,x(k)+.5*k1);
    k3 = h*fpop(t(k)+.5*h,x(k)+.5*k2);
    k4 = h*fpop(t(k)+h,x(k)+.5*k3);
    x(k+1) = x(k) + (k1 + 2*k2 + 2*k3 +k4)/6;
    t(k+1) = t(k) + h;
end
plot(t,x)
title('your name, your student number, lesson number')
xlabel('time')
ylabel('population')


