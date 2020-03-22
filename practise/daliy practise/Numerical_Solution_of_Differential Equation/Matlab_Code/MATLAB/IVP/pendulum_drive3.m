clear all; close all;

global K c

K=10; c=0.05;

t0=0; tfinal=500; y0=[3*pi/4,0.5];
[t,y]=ode45('pendulum_2',[t0,tfinal],y0);

y1=y(:,1); y2=y(:,2);
plot(t,y1)
xlabel('time')
ylabel('angle, \theta')
figure(2)
plot(y1,y2)
title('Phase plot')
xlabel('y1')
ylabel('y2')