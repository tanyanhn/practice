
clear; close all

 a = 0;  b=1; tfinal = 0.5; % Input the domain and final time.

 m = 20; h = (b-a)/m; k = h; mu = 1.5*k/h; % Set mesh and time step.
 
 t = 0; n = fix(tfinal/k);  % Find the number of time steps.
 y1 = zeros(m+1,1); y2=y1; x=y1;

 figure(1);  hold
 %axis([-0.1 1.1 -0.1 1.1]);
 
 for i=1:m+1,
   x(i) = a + (i-1)*h;
   y1(i) = uexact(t,x(i));   % Initial data
   y2(i) = 0;
 end

 % Time marching
 
 for j=1:n,
   y1(1)=bc(t); y2(1)=bc(t+k);
   for i=2:m+1
     y2(i) = y1(i) - mu*(y1(i)-y1(i-1) );
   end
   t = t + k;
   y1 = y2;
   plot(x,y2); pause(0.5);  % Add the solution plot to the history.
 end

 u_e = zeros(m+1,1);
 for i=1:m+1
   u_e(i) = uexact(t,x(i));
 end

 max(abs(u_e-y2))

 plot(x,y2,'o',x,u_e)
   

