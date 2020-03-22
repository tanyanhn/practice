% your name , your student number, lesson number
clear;
tf = 3;     
yo = [1 1];
[t y] = ode23s('ypcstiff',[0 tf],yo);
plot(t,y(:,1),t,y(:,2));
title('your name, your student number, lesson number')
xlabel('time')
ylabel('solutions one and two')
