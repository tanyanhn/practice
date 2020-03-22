close all; clear
y0=[1 1 1]; t0=0; M = moviein(20); 

for i=1:80,
   tspan=[i-1,i];  [x,y]=ode15s('chemistry',tspan,y0);
%   tspan=[i-1,i];  [x,y]=ode45('chemistry',tspan,y0);
   y1 = y(:,1); y2 = y(:,2); y3=y(:,3);
   k=length(y1); y0=[y(k,1),y(k,2),y(k,3)];
   plot3(y(k,1),y(k,2),y(k,3),'*')
   if i ==1 
       hold; axis([-1e4, 1e5,0 , 2000, -1e4, 3.4e4]); 
   end
   M(:,i) = getframe;       % There are 80 frames.
end
movie(M,5)      % Play 5 times.

