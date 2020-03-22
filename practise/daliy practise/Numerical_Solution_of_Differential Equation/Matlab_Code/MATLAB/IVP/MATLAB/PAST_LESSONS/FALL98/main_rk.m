
clear; close all;

x0=0;  y0 = [1,0];  xfinal = 2.1*pi; n=20;

[x, y] = euler1(x0,xfinal,'yfun2',y0,n);
y1=y(:,1); y2=y(:,2);
plot(y1,y2)
axis('square'); axis([-2 2 -2 2]) ; 

[x, y] = euler2(x0,xfinal,'yfun2',y0,n);
y1=y(:,1); y2=y(:,2);
figure(2); plot(y1,y2); axis('square'); axis([-2 2 -2 2]) ;

[x, y] = rk4_sol(x0,xfinal,'yfun2',y0,n);
y1=y(:,1); y2=y(:,2);
figure(3); plot(y1,y2); axis('square'); axis([-2 2 -2 2]) ;

[x, y] = ode45('yfun2',[x0,xfinal],y0);
y1=y(:,1); y2=y(:,2);
figure(4); plot(y1,y2); axis('square'); axis([-2 2 -2 2]) ;
