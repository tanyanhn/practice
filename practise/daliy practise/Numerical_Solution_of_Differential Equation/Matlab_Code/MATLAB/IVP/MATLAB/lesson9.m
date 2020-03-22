
clear all
global b c d e

b = 0.5;  c = 0.01;  d = 0.5;  e = 0.01;

t0 = 0; tfinal=50; y0 =[80, 100];

[t y] = ode45('yprf',[t0,tfinal],y0);

y1 = y(:,1); y2=y(:,2);            % Extract solution components.

figure(1); subplot(211); plot(t,y1);  title('Population of fox') 
subplot(212); plot(t,y2);             title('Population of rabbit')
print -dps plot1.ps

figure(2); plot(y1,y2)                % Phase plot
xlabel('fox'); ylabel('rabbit'); title('phase plot')
