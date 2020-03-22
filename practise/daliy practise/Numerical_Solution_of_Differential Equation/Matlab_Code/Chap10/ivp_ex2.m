clear all; close all;
[t,y] = ode23('yp' ,[0,5], [1,0]');
y1=y(:,1); y2=y(:,2);
subplot(3,1,1); plot(t,y1)
xlabel('t'); ylabel('y_1(t)')
subplot(3,1,2); plot(t,y2)
xlabel('t'); ylabel('y_2(t)')
subplot(3,1,3); plot(y1,y2)
xlabel('y_1'); ylabel('y_2')
print -depsc plot_IVP_ex2
