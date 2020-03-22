
disp('Welcome to Demo 2, the Euler methods for the system.')
disp('Strike any key when ready')
pause

clear; close
 
t0 = 0; t_final = 6.3; y0=[1 0]; n=40;                 
 
[tmesh,ysol] = euler2(t0,t_final,'yfun2',y0,n);

y1 = ysol(:,1); y2 = ysol(:,2);         % Extract solution component.

%%%%%% Below is the error analysis and plot(s) ---------------------

y1_exact = cos(tmesh);
y2_exact = sin(tmesh);
 
error1 = norm(y1_exact-y1,inf)          % Matlab function to masure the
error2 = norm(y2_exact-y2,inf)          % largest error
 
figure(1); plot(tmesh,y1,'o',tmesh,y1_exact,'-'); 
legend('Computed','Eaxct')
title('Exact solution and computed solution of y_1')

figure(2); plot(tmesh,y2,'o',tmesh,y2_exact,'-');
legend('Computed','Eaxct')
title('Exact solution and computed solution of y_2')
 
figure(3); plot(y1,y2);                  % Phase plot.
title('Error Plot')
 
figure(1); print -deps fig1.eps;      % Save the 1-st plot.
figure(2); print -deps fig2.eps;      % Save the 2-nd plot.
figure(3); print -deps fig3.eps;      % Save the 3-rd plot.

disp('You have successfully completed the Demo 2!')


