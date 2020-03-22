%your name, your student number, lesson number
clear;
to = 0;
tf =50;
yo = [80 100];
options = odeset('RelTol', 1e-5);
[t y] = ode45('yprf',[to tf],yo,options);
plot(y(:,1),y(:,2))
title('your name, your student number, lesson number')
ylabel('rabbits')
xlabel('fox')
%plot(t,y(:,1),t,y(:,2))
%xlabel('time')
%ylabel('rabbits and fox')
