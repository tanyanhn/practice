
clear all; close all; 

y0=[1 1 1]; t0=0; M = moviein(20); 
plot3(y0(1),y0(2),y0(3)); hold; axis([0.84 1 0.4 1 0.1 1]);

for i=1:80,
    tspan=0.5*[i-1,i];  [x,y]=ode23s('chemistry',tspan,y0);
%   tspan=[i-1,i];  [x,y]=ode45('chemistry',tspan,y0);
    [m,n]=size(y); y0=[y(m,1),y(m,2),y(m,3)];  % Get the last point.
    plot3(y(m,1),y(m,2),y(m,3),'*')
    M(:,i) = getframe;       % There are 80 frames.
end
movie(M,5)      % Play 5 times.

