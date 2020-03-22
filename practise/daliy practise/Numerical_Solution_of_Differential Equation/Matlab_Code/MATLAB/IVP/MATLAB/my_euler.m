
function [t,y] = my_euler(yfun,t_range,y0,n)

h = ( t_range(2)-t_range(1) )/n

mdim=length(y0);     		% how many equations are there?
t = zeros(n+1,1);

y=zeros(n+1,mdim);              % initialize y

y(1,:)=y0';	                % put the initial value in the first row.
t(1) = t_range(1);

for i=1:n
    y(i+1,:) = y(i,:) + h * feval(yfun,t(i),y(i,:))';  % Euler's method
    t(i+1) = t(i) + h;
end
