
clear all; close all

global a b

a = 1;   b=3;      % Test 1, Recover Figure 14.3
%a = 1;  b=20;     % Test 2, Test stiffness, take tfinal = 500

t0 = 0;  tfinal = 50;  y0=[1, 0.2];

  [t,y] = ode45('chem',[t0,tfinal],y0);
%  [t,y] = ode23('chem',[t0,tfinal],y0);
%[t,y] = ode23s('chem',[t0,tfinal],y0);

y1 = y(:,1); y2 = y(:,2); plot(t,y1)
subplot(211); plot(t,y1); xlabel('t'); ylabel('y_1(t)');
title('Solution plot y_1(t)')
subplot(212); plot(t,y2); xlabel('t'); ylabel('x(t)');
title('Solution plot y_2(t)')

figure(2); plot(y1,y2); xlabel('y_1'); ylabel('y_2'), title('Phase plot')


