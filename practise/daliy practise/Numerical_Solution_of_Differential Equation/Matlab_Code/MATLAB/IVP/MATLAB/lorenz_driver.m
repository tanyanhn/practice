
clear

global r

r =300; 
n = 400;

x0 = 0; xfinal = 20; y0 = [1.0,0,0];

%[y,x] = euler2_sol(x0,xfinal,'loren',y0,n);
%[x,y]  = euler1_simple(x0,xfinal,'loren',y0,n);
%[y,x] = rk4_sol(x0,xfinal,'loren',y0,n);

%[y,x] = rkf45_sol(x0,xfinal,'loren',y0,1e-6);
[x,y]  = ode45('loren',[x0,xfinal],y0);

y1 = y(:,1); y2 = y(:,2); y3 = y(:,3); 

figure(1); plot(x,y1) 
pause(2)
figure(2); plot(x,y2)
pause(2)
figure(3); plot(x,y3)
pause(2)
figure(4); plot3(y1,y2,y3)              % Phase plot.

