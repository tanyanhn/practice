% your name , your student number, lesson number
clear;
tf = 10;     
yo = [480 1.1 480];
[t y] = ode15s('yporeg',[0 tf],yo);
semilogy(t,y(:,1),t,y(:,2),t,y(:,3));
title('your name, your student number, lesson number')
xlabel('time')
ylabel('solutions one , two and three')
