
clear all; close all;
global a b c d

a = 0.5;  b = 0.01;  c = 0.5; d = 0.01; 

t0 = 0; tfinal=50; y0 =[100, 80];

 %y0 = [0.01 0.01];  tfinal=150;    %Test 2
% a=0.5; d=0.5; b=0.01; c=0.01; tfinal = 500;    % Test 3.

[t y] = ode23s('prey_prd',[t0,tfinal],y0);

y1 = y(:,1); y2=y(:,2);            % Extract solution components.

figure(1); subplot(211); plot(t,y1);  title('Population of prey') 
subplot(212); plot(t,y2);             title('Population of predator')
print -dps plot1.ps

figure(2); plot(y1,y2)                % Phase plot
xlabel('prey'); ylabel('predator'); title('phase plot')
