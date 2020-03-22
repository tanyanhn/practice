% Lesson 1, your name, your student number
clear;				   % This clears the memory.
for i = 0:50			% This starts the loop from time =0 to 50.
   time(i+1) = i;
   y(i+1) = temp(i);
end
plot(time,y)			%  Plots the graph and inserts title and labels.
title('Lesson 1, your name, your student number')
xlabel('time')
ylabel('temperature')
