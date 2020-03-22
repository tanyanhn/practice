%your name, your student number, lesson number
clear;
yo = [1];
to = 0;
tf = 200;
[t y] = ode45('ypinfo',[to tf],yo);
plot(t,y)
title('your name, your student number , lesson number')
xlabel( 'time')
ylabel( 'informed')
