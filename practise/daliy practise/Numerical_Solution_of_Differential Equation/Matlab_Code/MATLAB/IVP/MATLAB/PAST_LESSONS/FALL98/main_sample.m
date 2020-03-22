
clear; close all

global a b c d e f g h

a = 1;  b=2;  c=1;  d=1; e=3;  f=1;  g=1;  h=1;

t0 = 0; t_final=100; y0=[1,1,1]; n=200;
%[t, y] = euler2(t0,t_final,'sample_f',y0,n);
[t, y] = ode45('sample_f',[t0,t_final],y0);    % Note: n is not needed.

%--- Plot the solution.

y1=y(:,1); y2=y(:,2); y3=y(:,3);
figure(1); plot(t,y1); xlabel('t'); ylabel('y_1');title('Carnivores')
figure(2); plot(t,y2); xlabel('t'); ylabel('y_2'); title('Vegetarians')
figure(3); plot(t,y3); xlabel('t'); ylabel('y_3'); title('Plants')
figure(4); plot3(y1,y2,y3); xlabel('y_1'); ylabel('y_2');title('Phase Plot')

% Clean figure(1), figure(2), figure(3) after 10 seconds
pause(20)
close figure(1), figure(2), figure(3);

%Put several picture together:
figure(1); plot(t,y1,t,y2,t,y3)

% Save figure(1) and figure(4) to files:

figure(1); print -deps plot1.eps
figure(4); print -deps plot2.eps


