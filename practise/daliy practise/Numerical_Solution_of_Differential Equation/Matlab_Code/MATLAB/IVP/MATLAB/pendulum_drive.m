
clear all; close all

global m c k

% m = 1; c=0; k=1;           % Test 1.
% m = 1; c=0.1; k=1;           % Test 2.
m =1; c=0.1; k=10;           % Test 3.    Expect more oscillations!
t0 = 0;  tfinal = 50;  y0=[pi/4, 0];
[t,y] = ode45('pendulum',[t0,tfinal],y0);
y1 = y(:,1); y2 = y(:,2); plot(t,y1)
xlabel('t'); ylabel('\theta');title('Solution plot')
figure(2); plot(y1,y2); xlabel('y1'); ylabel('y1'), title('Phase plot')


