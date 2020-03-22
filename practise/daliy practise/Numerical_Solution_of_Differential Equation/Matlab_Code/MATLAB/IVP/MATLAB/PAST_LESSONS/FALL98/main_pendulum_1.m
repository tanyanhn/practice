
clear; close all

global w

w = 1;
t0 = 0;  tfinal = 50;  y0=[pi/4, 0];
[t,y] = ode45('pendulum_1',[t0,tfinal],y0);
y1 = y(:,1); plot(t,y1)
xlabel('t'); ylabel('\theta');title('w = 1, y0=[pi/4, 0]')

w = 3;

t0 = 0;  tfinal = 50;  y0=[pi/4, 0];
[t,y] = ode45('pendulum_1',[t0,tfinal],y0);
y1 = y(:,1); figure(2); plot(t,y1)
xlabel('t'); ylabel('\theta');title('w = 3, y0=[pi/4, 0]')

w = 1;
t0 = 0;  tfinal = 50;  y0=[pi/2, 0];
[t,y] = ode45('pendulum_1',[t0,tfinal],y0);
y1 = y(:,1); figure(3); plot(t,y1)
xlabel('t'); ylabel('\theta');title('w = 1, y0=[pi/2, 0]')

