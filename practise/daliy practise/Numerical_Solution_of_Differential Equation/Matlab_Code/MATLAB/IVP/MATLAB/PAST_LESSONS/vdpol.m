% your name , your student number, lesson number
clear;
tf = 10;     % choose tf about ten times mu
yo = [2 0];
[t y] = ode23s('ypvdpol',[0 tf],yo);
plot(t,y(:,1));
title('your name, your student number, lesson number')
xlabel('time')
ylabel('charge')
%plot(y(:,1),y(:,2));