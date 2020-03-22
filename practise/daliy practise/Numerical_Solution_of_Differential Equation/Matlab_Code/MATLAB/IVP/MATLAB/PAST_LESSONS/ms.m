%your name, your student number, lesson number
clear;
t0 = 0;
tf = 100;
y0 = [0 0];
[t y] = ode45('ypms', [t0 tf],y0);
plot(t,y(:,1))
title( 'your name, your student number, lesson number')
xlabel('time')
ylabel('displacement')
%plot(y(:,1),y(;,2));