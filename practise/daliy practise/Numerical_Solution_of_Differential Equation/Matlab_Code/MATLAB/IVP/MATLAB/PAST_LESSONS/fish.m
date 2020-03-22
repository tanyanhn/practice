%your name, your student number, lesson number
clear;
yo = [1];
to = 0;
tf = 20;
[t y] = ode45('ypfish',[to tf],yo);
plot(t,y)
title('your name, your student number , lesson number')
xlabel( 'time')
ylabel( 'population size')
