%your name, your student number, lesson number
clear;
t0 = 0;
tf = .3;
y0 = [0 0];
[t y] = ode45('yptune', [t0 tf],y0);
plot(t,y(:,2))
title( 'your name, your student number, lesson number')
xlabel('time')
ylabel('current')
%plot(y(:,1),y(;,2));