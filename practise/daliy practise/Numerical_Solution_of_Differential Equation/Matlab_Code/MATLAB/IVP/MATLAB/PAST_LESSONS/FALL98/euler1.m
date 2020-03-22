function [x,y] = euler1(x0,xfinal,yfun,y0,n)

h=(xfinal-x0)/n;

mdim=length(y0);	 % Find how many dependent variables, y's.

y=zeros(n+1,mdim);	 % Open a space for the solution.
x = zeros(n+1,1);        % Return x as a column vector.

y(1,:)=y0;               % First row is the initial value at x0. 

x(1)=x0; 

for i=1:n
    y(i+1,:)=y(i,:)+h*feval(yfun,x(i),y(i,:))';   % do all rows!
    x(i+1) = x(i) + h;
end
