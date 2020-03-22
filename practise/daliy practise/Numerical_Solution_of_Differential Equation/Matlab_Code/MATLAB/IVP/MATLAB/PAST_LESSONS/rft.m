%your name, your student number, lesson number
clear;
to = 0;
tf =20;
yo = [100 90 80];
[t y] = ode45('yprft',[to tf],yo);
plot(t,y(:,1),t,y(:,2),t,y(:,3))
title('your name, your student number, lesson number')
xlabel('time')
ylabel('rabbits, fox,turkeys')