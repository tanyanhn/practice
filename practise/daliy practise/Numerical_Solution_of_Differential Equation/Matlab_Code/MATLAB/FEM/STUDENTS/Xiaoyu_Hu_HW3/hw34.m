clear all;
close all;

x=-1:0.001:1;
c=9/16;
y1=-c.*(x-1).*(x-1/3).*(x+1/3);
y2=c.*(x-1).*(x-1/3).*(x+1);
y3=-c.*(x-1).*(x+1/3).*(x+1);
y4=c.*(x+1).*(x-1/3).*(x+1/3);

plot(x,y1);
hold on
plot(x,y2);
plot(x,y3);
plot(x,y4);