clear all; close all;

global a b c d

a=1; b=1; c=1; d=1;

t0=0; tfinal=500; y0=[100,20.5];
[t,y]=ode15s('prey_pred_2',[t0,tfinal],y0);

y1=y(:,1); y2=y(:,2);
subplot(211); plot(t,y1)
xlabel('time')
ylabel('population of prey')
subplot(212); plot(t,y2)
xlabel('time')
ylabel('population of predator')
figure(2)
plot(y1,y2)
title('Phase plot')
xlabel('prey')
ylabel('predator')