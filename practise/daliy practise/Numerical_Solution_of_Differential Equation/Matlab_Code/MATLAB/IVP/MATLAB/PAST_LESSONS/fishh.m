global c M
y0=0.374; t0=0; c=1/18; M=10; tfinal =200;
[t y] = ode45('ypfishh',[t0,tfinal],y0);
plot(t,y)
xlabel('time')
ylabel('Population')
