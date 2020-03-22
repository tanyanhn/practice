clear all; close all;
global a 

a = 0.5;  

t0 = 0; tfinal=5; y0 =[1.5, 1.0003];

y0 = [0.01 0.01];  tfinal=200;  

[t y] = ode23s('prey_prd',[t0,tfinal],y0);

y1 = y(:,1); y2=y(:,2);            % Extract solution components.

figure(1); subplot(211); plot(t,y1);  title('Population of prey') 
subplot(212); plot(t,y2);             title('Population of predator')
print -deps y_vs_time_prey_prd.eps

figure(2); plot(y1,y2)                % Phase plot
xlabel('prey'); ylabel('predator'); title('phase plot')
print -depsc phase_prey_prd.eps
