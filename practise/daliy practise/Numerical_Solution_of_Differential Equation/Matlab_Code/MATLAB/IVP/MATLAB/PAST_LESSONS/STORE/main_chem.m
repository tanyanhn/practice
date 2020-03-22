
clear all; close all

flops(0);
tspan=[0,1000]; y0=[1 1 1]; 
%[x,y]=ode15s('chemistry',tspan,y0);
%[x,y]=ode23s('chemistry',tspan,y0);
options = odeset('reltol',1e-4, 'Stats', 'on');      % Set certain options.
[x,y]=ode23s('chemistry',tspan,y0,options);
flops
y1 = y(:,1); y2 = y(:,2); y3=y(:,3);

figure(1); plot(x,y1) 
figure(2); plot(x,y2)
figure(3); plot(x,y3)

figure(4); plot3(y1,y2,y3); axis('square');               % Phase plot.

disp('Strike any key to continue')
disp(' ')
pause

close all

figure(1); semilogy(x,y1); 
%axis([0,20,0.1,1e6]);
figure(2); semilogy(x,y2)
figure(3); semilogy(x,y3)





