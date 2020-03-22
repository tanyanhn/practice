
clear all; close all;

global d e et k M c kt Mt ct

d = 0.5; e=0.01; et = 0.02;
k = 0.01; M=100; c = 0.01;
kt= 0.04; Mt=80; ct = 0.03;

t0 = 0; tf =20;

y0 = [100 90 80];

[t y] = ode45('yprft',[t0 tf],y0);

y1 = y(:,1); y2=y(:,2); y3=y(:,3);

plot(t,y1,t,y2,t,y3)       % Solution against time.

xlabel('time')
ylabel('Population of fox, rabbits, turkeys')

figure(2); plot3(y1,y2,y3);    % Phase plot.
