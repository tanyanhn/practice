
x0=1; y0=2; xfinal=3; n1=20;
[x1,y1] = euler_simple_f(x0,y0,xfinal,n1,'f4');

plot(x1,y1,'o')
hold
[x1,y1] = euler_simple_f(x0,y0,xfinal,160,'f4');
plot(x1,y1)


