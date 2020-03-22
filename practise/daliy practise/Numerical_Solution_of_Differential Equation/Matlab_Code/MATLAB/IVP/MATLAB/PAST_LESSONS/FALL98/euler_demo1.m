
disp('Welcome to Demo 1, the Euler method. Strike any key when ready')
pause


clear; close
 
t0 = 0; t_final = 1; y0= [ 1 ]; n=80;                 
 
%[tmesh,ysol] = euler1(t0,t_final,'yfun1',y0,n);
[tmesh,ysol] = euler2a(t0,t_final,'yfun1',y0,n);

%%%%%% Below is the error analysis and plot(s) ---------------------

y_exact = exp(-tmesh);
 
error = norm(y_exact-ysol,inf)          % Matlab function to masure the
                                        % largest error
 
figure(1); plot(tmesh,ysol,'o',tmesh,y_exact,'-'); 
legend('Computed','Eaxct')
title('Exact solution and computed solution')
 
figure(2); plot(tmesh,ysol-y_exact);      % Error plot.
title('Error Plot')
 
disp('Use mouse to move away figure 2 to see both plots.')
disp('Then sttrike any key to continue')
pause

figure(1); print -deps fig1.eps;      % Save the 1-st plot.
figure(2); print -deps fig2.eps;      % Save the 2-nd plot.

disp('You have successfully completed the Demo 1!')


